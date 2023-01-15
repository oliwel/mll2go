package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
)

var default_sketch = `
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "MobaLedLib.h"
#define NUM_LEDS _NUM_LEDS
#define LED_DO_PIN 6

CRGB leds[NUM_LEDS];
MobaLedLib_Create(leds);
LED_Heartbeat_C LED_Heartbeat(LED_BUILTIN);

void setup(){
  FastLED.addLeds<NEOPIXEL, LED_DO_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
}

void loop(){
  MobaLedLib.Update();
  FastLED.show();
  LED_Heartbeat.Update();
}
`

func buildHeaderTemplate(filePath string, lednum int) ([]string, error) {

	readFile, err := os.Open(filePath)
	defer readFile.Close()

	if err != nil {
		log.Fatalf("Reading file failed with '%s'\n", err)
	}
	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)
	var outLines []string

	for fileScanner.Scan() {

		var line = fileScanner.Text()
		if strings.Contains(line, "NUM_LEDS") {
			outLines = append(outLines, fmt.Sprintf("#define NUM_LEDS %01d", lednum))
		} else {
			outLines = append(outLines, line)
		}
	}
	return outLines, nil
}

func readItem(filePath string, itemOffset int) ([]string, int, error) {

	readFile, err := os.Open(filePath)
	defer readFile.Close()

	if err != nil {
		log.Fatalf("Reading file failed with '%s'\n", err)
	}
	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)
	var outLines []string
	var currentLine string
	ledCount := 0
	ledNumPattern := regexp.MustCompile("^\\s*(\\w+)\\(\\s*(\\d+)\\s*\\D")

	var isReading = false
	for fileScanner.Scan() {

		var line = fileScanner.Text()
		if strings.HasPrefix(line, "## MLL") {
			isReading = true
			continue
		}

		if !isReading {
			continue
		}

		if strings.HasPrefix(line, "#") {
			return outLines, ledCount, nil
		}

		// skip blank lines
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}

		// opening bracket, scan and replace LED number
		if strings.Contains(line, "(") {

			patternResult := ledNumPattern.FindStringSubmatch(line)
			// ["HouseT( 0," "HouseT" "0"]
			//fmt.Printf("%q\n", patternResult)
			if len(patternResult) != 3 {
				continue
			}

			ledOffset, err := strconv.Atoi(patternResult[2])
			if err != nil {
				log.Fatalf("Unable to convert LED number in '%s'", patternResult[2])
			}

			if patternResult[1] == "AddLedCount" {
				ledCount += ledOffset
				continue
			}

			ledCount = itemOffset + ledOffset

			if patternResult[1] == "SetLedCount" {
				return outLines, ledCount, nil
			}

			line = strings.Replace(line, patternResult[0], fmt.Sprintf("%s(%1d, ", patternResult[1], itemOffset+ledOffset), 1)
			currentLine = line
		}

		if currentLine != "" {
			currentLine += line
		}

		// If it has a closing bracket, the command is complete
		if strings.HasSuffix(line, ")") {
			outLines = append(outLines, currentLine)
			currentLine = ""
		}
	}

	return outLines, ledCount, nil
}

func writeFile(filename string, content []string) error {

	var f *os.File
	var err error
	if filename == "" {
		f = os.Stdout
	} else {
		f, err = os.Create(filename)
		if err != nil {
			log.Fatalf("failed creating file: %s", err)
		}
	}
	defer f.Close()
	for _, line := range content {
		_, err := f.WriteString(line + "\n")
		if err != nil {
			log.Fatalf("failed writing to file: %s", err)
		}
	}
	return nil
}

func main() {

	var configLines = []string{
		"MobaLedLib_Configuration() {",
		"RGB_Heartbeat(0)",
	}
	var outLines []string

	uploaderPtr := flag.String("u", "", "name of uploader script")
	dryrunPtr := flag.Bool("n", false, "dry-run (print config section only)")

	flag.Parse()

	itemOffset := 0
	files := flag.Args()
	if len(files) < 1 {
		log.Fatalf("Please provide name(s) of file to read as arguments")
	}

	for _, filename := range files {
		outLines, itemOffset, _ = readItem(filename, itemOffset)
		if len(outLines) == 0 {
			continue
		}
		configLines = append(configLines, "// "+filename)
		configLines = append(configLines, outLines...)
	}
	configLines = append(configLines, "// Final Heartbeat", fmt.Sprintf("RGB_Heartbeat(%01d)", itemOffset+1), "};")

	if *dryrunPtr {
		writeFile("", configLines)
		os.Exit(0)
	}

	info, err := os.Stat("LEDs_AutoProg")
	var uploadFile string
	if err == nil && info.IsDir() {
		allLines, _ := buildHeaderTemplate("LEDs_AutoProg/LEDs_AutoProg.h.tpl", itemOffset+10)
		allLines = append(allLines, configLines...)
		writeFile("LEDs_AutoProg/LEDs_AutoProg.h", allLines)
		uploadFile = "LEDs_AutoProg/LEDs_AutoProg.ino"
		fmt.Println("Wrote LEDs_AutoProg.h")
	} else {
		head := strings.Replace(default_sketch, "_NUM_LEDS", strconv.Itoa(itemOffset+10), 1)
		var allLines = []string{head}
		allLines = append(allLines, configLines...)

		// Upload is set, write to tempdir and run script (later)
		if *uploaderPtr != "" {
			tmpDir, err := os.MkdirTemp("", "mll*")
			if err != nil {
				log.Fatal(err)
			}
			filename := filepath.Base(tmpDir)
			uploadFile = tmpDir + "/" + filename + ".ino"
			defer os.RemoveAll(tmpDir)
		}
		// if uploadFile is empty this prints to STDOUT
		writeFile(uploadFile, allLines)
	}

	if *uploaderPtr != "" {
		fmt.Println("Running uploader for " + uploadFile)
		cmd := *uploaderPtr
		_, err := exec.Command(cmd, uploadFile).Output()
		if err != nil {
			log.Fatal(err)
		}
	}
}

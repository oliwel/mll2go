package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

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
	ledNumPattern := regexp.MustCompile("^(\\w+)\\(\\s*(\\d+)\\D")

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

			line = strings.Replace(line, patternResult[0], fmt.Sprintf("%s(%1d", patternResult[1], itemOffset+ledOffset), 1)
		}

		currentLine += line

		// If it has a closing bracket, the command is complete
		if strings.Contains(line, ")") {
			outLines = append(outLines, currentLine)
			currentLine = ""
		}
	}

	return outLines, ledCount, nil
}

func main() {

	var allLines []string
	var outLines []string
	allLines = append(allLines, "RGB_Heartbeat(0)")

	itemOffset := 0
	fileCnt := len(os.Args) - 1
	if fileCnt < 1 {
		log.Fatalf("Please provide name(s) of file to read")
	}

	for i := 1; i <= fileCnt; i++ {
		filePath := os.Args[i]
		outLines, itemOffset, _ = readItem(filePath, itemOffset)
		allLines = append(allLines, "# "+filePath)
		allLines = append(allLines, outLines...)
	}
	allLines = append(allLines, "# Final Heartbeat", fmt.Sprintf("RGB_Heartbeat(%01d)", itemOffset+1))

	for _, line := range allLines {
		fmt.Println(line)
	}

}

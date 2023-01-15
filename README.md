# Configuration and Tools for Oli's MobaLedLib

## Purpose

Grab MLL configuration rules from text files and compile them into
a format that can be uploaded to the arduino. 

## Rules Files

Create one file per house holding its MLL configuration. 

The file can contain arbitrary information as long as there is a section
that starts with `## MLL Konfiguration`. The converter tries to find 
configuration terms in the following lines as defined in 
https://wiki.mobaledlib.de/anleitungen/effekte_mll.

- a command line must start with `Command(` 
- the command can span over multiple lines for readability, those are just concatenated together
- a line that contains with a closing bracket `)` terminates a command 
- any text outside of brackets is ignored
- processing ends on the next line starting with `#` or with the `SetLedCount` command 
- in each file the first LED must use the index 1  
### Command Processing

The first argument is interpreted as the LED number and replaced by a 
calculated value. It is expected, that the first LED in each item file 
has the value `1` and all further commands in the same file use the proper
offset based on this value. The value of the last definition is carried 
over as offset for the next item file. In case the last command spans 
over more than one address you need to tell the parser to add those with
the special command *AddLedCount(42)*. 

As an alternative you can use *SetLedCount* to set the total number of
LEDs used by an item. Note that this command will terminate processing 
of the current file. 

### Example

```
## MLL Konfiguration

HouseT( 1,   SI_1, 1, 4, 1, 3, ROOM_TV0_CHIMNEYB, ROOM_BRIGHT, ROOM_WARM_W, NEON_LIGHT)
ConstRGB(5 , SI_1, 100, 45, 45, 100, 45, 70)
HouseT(  6 ,   SI_1, 0,  1, 5, 35, GAS_LIGHT, NEON_LIGHT)
AddLedCount(1)
```

Instead of `AddLedCount(1)` you can also call `SetLedCount(7)`.

## Sketch Creation

Run the tool with the list of text files you want to process as argument.

### Using LEDs_AutoProg

Create the folder `LEDs_AutoProg` (copy it from the MLL base repository) and
create the file `LEDs_AutoProg.h.tpl` with the basic header information that 
are required. The file is then appended with the extracted rules and written 
as `LEDs_AutoProg.h`.

### Creating a standalone sketch

If the `LEDs_AutoProg` does not exist, the configuration is dumped to the 
console using some header lines that are built into the script.

### Automatic Upload

Create a shell script that contains the commands to upload the sketch and 
provide the path as  `mll2go -u bin/upload.sh ...`. The path to the sketch 
will be passed as argument.

### Debug

If you pass `-n` as option, the script will only print the configuration
section to the console.

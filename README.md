# Configuration and Tools for Oli's MobaLedLib

Create one file per MLL item holding its MLL configuration.

The block must start with a line `## MLL Konfiguration`, 
any subsequent line must contain a MLL command as defined in 
https://wiki.mobaledlib.de/anleitungen/effekte_mll.

The first argument is interpreted as the LED number and replaced by a 
calculated value. It is expected, that the first LED in eacht item file 
has the value `1` and all further commands in the same file use the proper
offset based on this value. The value of the last definition is carried 
over as offset for the next item file, so in case the last command spans 
over more than one address you need to tell the parser to add those with
the special command *AddLedCount(42)*. 

As an alternative you can use *SetLedCount* to set the total number of
LEDs used by an item. Note that this command will terminate processing 
of the current file. 

## Example

```
## MLL Konfiguration

HouseT( 1,   SI_1, 1, 4, 1, 3, ROOM_TV0_CHIMNEYB, ROOM_BRIGHT, ROOM_WARM_W, NEON_LIGHT)
ConstRGB(5 , SI_1, 100, 45, 45, 100, 45, 70)
HouseT(  6 ,   SI_1, 0,  1, 5, 35, GAS_LIGHT, NEON_LIGHT)
AddLedCount(1)
```

Instead of `AddLedCount(1)` you can also call `SetLedCount(7)`.

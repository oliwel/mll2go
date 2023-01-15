#define FASTLED_INTERNAL // Disable version number message in FastLED library (looks like an error)
#include "FastLED.h"     // The FastLED library must be installed in addition if you got the error message "..fatal error: FastLED.h: No such file or directory"
                         // Arduino IDE: Sketch / Include library / Manage libraries                    Deutsche IDE: Sketch / Bibliothek einbinden / Bibliothek verwalten
                         //              Type "FastLED" in the "Filter your search..." field                          "FastLED" in das "Grenzen Sie ihre Suche ein" Feld eingeben
                         //              Select the entry and click "Install"                                         Gefundenen Eintrag auswaehlen und "Install" anklicken

//#define HOUSE_MIN_T  2  // Minimal time [s] to the next event (1..255)
//#define HOUSE_MAX_T 5  // Maximal random time [s]              "

#define _FAST_TIMES
#define _PRINT_DEBUG_MESSAGES 1

#include "MobaLedLib.h"  // Use the Moba Led Library

#define NUM_LEDS     40  // Number of LEDs with some spare channels (Maximal 256 RGB LEDs could be used)
#define LED_DO_PIN   6   // Pin D6 is connected to the LED stripe


//---------------------------------------------
void Set_Start_Values(MobaLedLib_C &MobaLedLib)
//---------------------------------------------
{
}

LED_Heartbeat_C LED_Heartbeat(LED_BUILTIN); // Use the build in LED as heartbeat

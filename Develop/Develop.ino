#define FASTLED_INTERNAL // Disable version number message in FastLED library (looks like an error)
#include "FastLED.h"     // The FastLED library must be installed in addition if you got the error message "..fatal error: FastLED.h: No such file or directory"
                         // Arduino IDE: Sketch / Include library / Manage libraries                    Deutsche IDE: Sketch / Bibliothek einbinden / Bibliothek verwalten
                         //              Type "FastLED" in the "Filter your search..." field                          "FastLED" in das "Grenzen Sie ihre Suche ein" Feld eingeben
                         //              Select the entry and click "Install"                                         Gefundenen Eintrag auswaehlen und "Install" anklicken

//#define HOUSE_MIN_T  10  // Minimal time [s] to the next event (1..255)
//#define HOUSE_MAX_T 10  // Maximal random time [s]              "

#define PRINT_DEBUG_MESSAGES 1

#define GAS_MIN_T 1
#define GAS_MAX_T 3

#include "MobaLedLib.h"  // Use the Moba Led Library

#define NUM_LEDS     40  // Number of LEDs with some spare channels (Maximal 256 RGB LEDs could be used)
#define LED_DO_PIN   6   // Pin D6 is connected to the LED stripe

//*******************************************************************
// *** Configuration array which defines the behavior of the LEDs ***
MobaLedLib_Configuration(){
    //   LED:                   First LED number in the stripe
    //    |    InCh:            Input channel. Here the special input 1 is used which is always on
    //    |    |    On_Min:     Minimal number of active rooms. At least two rooms are illuminated.
    //    |    |    |   On_Max: Number of maximal active lights.
    //    |    |    |   |       rooms: List of room types (see documentation for possible types).
    //    |    |    |   |       |

    /*
      // 3x WS2811 + 5 LED = EG/OG
      // RGB Balkon + RGB 2 OG
      House(0,   SI_1,  8, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M,
        ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W )

      // 4x WS2811 (Garage Rückseite + Dach, Garage Front, 6x Halle)
      House(10,   SI_1,  8, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M)
      GasLights(12, SI_1, NEON_LIGHT1, NEON_LIGHT2, NEON_LIGHT3, NEON_LIGHT1, NEON_LIGHT2, NEON_LIGHT3)

      // 6x RGB (Garage 1 OG Front)
      House(14, SI_1, 0, 6, ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W )

      //ConstRGB(0, SI_1, 100, 45, 45, 100, 45, 70)
      //ConstRGB(1, SI_1, 100, 45, 45, 100, 45, 70)
      //ConstRGB(2, SI_1, 100, 45, 45, 100, 45, 70)

      // Feuerwache links
      // 3x WS2811 (P1=links, P2=rechts, P3 R=EG rechts G=Eingang B=2OG Giebel) + 5 LED = EG/OG
      // RGB Balkon + RGB 2 OG
      House(20,   SI_1,  4, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M,
        ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W )

      // Feuerwache Turm
      // P1 = Turm unten, P2 = Turm oben, P3 = R=Warnlicht G=Turmhaus B=Turm unten
      // 3 x RGB LED Turm oben
      House(30,   SI_1,  4, 9, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, SKIP_ROOM,
        ROOM_TV1, ROOM_WARM_W, ROOM_TV1)
      Blink2(32, C_RED, SI_1, 300, 1500, 0, 127)
      Const(32, C_BLUE, SI_1, 0, 80)
      Const(32, C_GREEN, SI_1, 0, 80)
    */
    /*
    RGB_Heartbeat(0)
    *//*
Blink2(0, C_RED, SI_1, 250, 500, 0, 10)
Blink2(0, C_BLUE, SI_1, 350, 250, 0, 50)
Blink2(0, C_GREEN, SI_1, 500, 800, 0, 20)

Blink2(1, C_RED, SI_1, 600, 300, 0, 10)
Blink2(1, C_BLUE, SI_1, 250, 150, 0, 30)
Blink2(1, C_GREEN, SI_1, 150, 400, 0, 50)

Blink2(2, C_RED, SI_1, 800, 200, 0, 10)
Blink2(2, C_BLUE, SI_1, 200, 600, 0, 50)
Blink2(2, C_GREEN, SI_1, 150, 250, 0, 20)

Blink2(3, C_RED, SI_1, 170, 250, 0, 50)
Blink2(3, C_BLUE, SI_1, 200, 450, 0, 30)
Blink2(3, C_GREEN, SI_1, 420, 100, 0, 40)

Flash(4, C_ALL, 42, 2, 100, 250)
Random(42, SI_1, RM_NORMAL, 30 Sec, 2 Min, 5 Sec, 20 Sec)*/

PatternT4(5, _NStru(C_RED, 4, 1), SI_1, _Cx2LedCnt(C_RED), 0, 255, 0, 0, 1000 ms, 500 ms, 1000 ms, 1500 ms, _Cx2P_DBLFL(C_RED))

    // P2 - Stellwerk - EG Nebenraum, EG Eingang, OG hinten, OG vorne, Schaltraum, Außenlicht
    // HouseT(0,   SI_1, 1, 4, 1, 3, ROOM_TV0_CHIMNEYB, ROOM_BRIGHT, ROOM_WARM_W, NEON_LIGHT)
    // ConstRGB(4, SI_1, 100, 45, 45, 100, 45, 70)
    // HouseT(5,   SI_1, 0,  1, 5, 35, GAS_LIGHT)
    // RGB_Heartbeat(6)

    /*
    RGB_Heartbeat(3)
    RGB_Heartbeat(4)

    // vorne
    RGB_Heartbeat(5)

    RGB_Heartbeat(6)
    RGB_Heartbeat(7)


    RGB_Heartbeat(8)
    RGB_Heartbeat(9)

    RGB_Heartbeat(10)
    RGB_Heartbeat(11)
    RGB_Heartbeat(12)

    RGB_Heartbeat(13)
    RGB_Heartbeat(14)
    RGB_Heartbeat(15)




      // P1 - Bahnsteig Nebenbahn - Unterführung + Kiosk + 7 Deckenleuchten
      /*House(1,   SI_1,  1, 1, ROOM_TV1 ) // Unterführung
      House(2,   SI_1,  1, 1, ROOM_TV0 ) // Kiosk
      GasLights(3, SI_1, NEON_LIGHTM, NEON_DEF_D, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_DEF_D )

      // P2 - Stellwerk - EG Nebenraum, EG Eingang, OG hinten, OG vorne, Schaltraum, Außenlicht
      House(10,   SI_1, 2,  6, ROOM_TV0_CHIMNEYB, ROOM_BRIGHT, ROOM_WARM_W, NEON_LIGHT)
      ConstRGB(14, SI_1, 100, 45, 45, 100, 45, 70)
      House(15,   SI_1, 1,  1, GAS_LIGHT)

      // P3 - Bahnsteig Hauptgebäude - 12 Neonleuchten (7 Hauptgebäude + 5 Außenbahnsteig)
      GasLights(16, SI_1, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM,
        NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM)

      // P4 - E-Lokschuppen, 3 Neon + Schweißlicht
      Welding(28, SI_1)
      House(29,   SI_1, 3,  3, NEON_LIGHT, NEON_LIGHT, NEON_LIGHT)

      // P5- Bahnsteig mit Strassenlaternen - 3x3 Kanäle
      GasLights(32, SI_1, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M )

      //RGB_Heartbeat(34)
       */
    EndCfg // End of the configuration
};
//*******************************************************************


CRGB leds[NUM_LEDS];     // Define the array of leds

MobaLedLib_Create(leds); // Define the MobaLedLib instance

LED_Heartbeat_C LED_Heartbeat(LED_BUILTIN); // Use the build in LED as heartbeat

//----------
void setup(){
//----------
// This function is called once to initialize the program
//
  FastLED.addLeds<NEOPIXEL, LED_DO_PIN>(leds, NUM_LEDS); // Initialize the FastLED library

  #ifdef _PRINT_DEBUG_MESSAGES
    Serial.begin(9600); // Attention: The serial monitor in the Arduino IDE must use the same baudrate
  #endif
}

//---------
void loop(){
//---------
// This function contains the main loop which is executed continuously
//
  MobaLedLib.Update();    // Update the LEDs in the configuration

  FastLED.show();         // Show the LEDs (send the leds[] array to the LED stripe)
  LED_Heartbeat.Update(); // Update the heartbeat LED. This must be called periodically in the loop() function.
}


/*
 Arduino Nano:          +-----+
           +------------| USB |------------+
           |            +-----+            |
        B5 | [ ]D13/SCK        MISO/D12[ ] |   B4
           | [ ]3.3V           MOSI/D11[ ]~|   B3
           | [ ]V.ref     ___    SS/D10[ ]~|   B2
        C0 | [ ]A0       / N \       D9[ ]~|   B1
        C1 | [ ]A1      /  A  \      D8[ ] |   B0
        C2 | [ ]A2      \  N  /      D7[ ] |   D7
        C3 | [ ]A3       \_0_/       D6[ ]~|   D6   -> WS281x LED stripe pin DIN
        C4 | [ ]A4/SDA               D5[ ]~|   D5
        C5 | [ ]A5/SCL               D4[ ] |   D4
           | [ ]A6              INT1/D3[ ]~|   D3
           | [ ]A7              INT0/D2[ ] |   D2
           | [ ]5V                  GND[ ] |
        C6 | [ ]RST                 RST[ ] |   C6
           | [ ]GND   5V MOSI GND   TX1[ ] |   D0
           | [ ]Vin   [ ] [ ] [ ]   RX1[ ] |   D1
           |          [ ] [ ] [ ]          |
           |          MISO SCK RST         |
           | NANO-V3                       |
           +-------------------------------+

 Arduino Uno:                           +-----+
           +----[PWR]-------------------| USB |--+
           |                            +-----+  |
           |           GND/RST2  [ ] [ ]         |
           |         MOSI2/SCK2  [ ] [ ]  SCL[ ] |   C5
           |            5V/MISO2 [ ] [ ]  SDA[ ] |   C4
           |                             AREF[ ] |
           |                              GND[ ] |
           | [ ]N/C                    SCK/13[A] |   B5
           | [ ]v.ref                 MISO/12[A] |   .
           | [ ]RST                   MOSI/11[A]~|   .
           | [ ]3V3    +---+               10[ ]~|   .
           | [ ]5v     | A |                9[ ]~|   .
           | [ ]GND   -| R |-               8[B] |   B0
           | [ ]GND   -| D |-                    |
           | [ ]Vin   -| U |-               7[A] |   D7
           |          -| I |-               6[A]~|   .   -> WS281x LED stripe pin DIN
           | [ ]A0    -| N |-               5[C]~|   .
           | [ ]A1    -| O |-               4[A] |   .
           | [ ]A2     +---+           INT1/3[A]~|   .
           | [ ]A3                     INT0/2[ ] |   .
      SDA  | [ ]A4      RST SCK MISO     TX>1[ ] |   .
      SCL  | [ ]A5      [ ] [ ] [ ]      RX<0[ ] |   D0
           |            [ ] [ ] [ ]              |
           |  UNO_R3    GND MOSI 5V  ____________/
            \_______________________/
*/

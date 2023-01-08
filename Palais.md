# Palais "Goethe 88"

port: 2:2

11x RGB, 3xWS2821

1x Fenster EG
2x Laden Front
2x Laden seitlich
# Palais / Eckhaus Goethestrasse

## Beschreibung

Erker rechts 2. OG
Zimmer rechts, 3. OG
Erker front, 3. OG
Eckzimmer links, 2. OG
Zimmer rechts 2. OG
Erker links 1. OG
R: Erker front 1.OG G: Fenster rechts 1.OG  B: Fenster links hinten, 2.OG 
R: Fenster rechts hinten, 3. OG G: Fenster Front 2.OG B: Fenster rechts 2.OG
R: Alarmanlage, G: Dach, B: leer


## MLL Konfiguration

House(1, SI_1, 0, 1, ROOM_TV1_CHIMNEYB)
House(2, SI_1, 1, 4, ROOM_TV1, ROOM_TV0, NEON_LIGHTM, NEON_LIGHTM)
House(6, SI_1, 6, 12,
    ROOM_CHIMNEYD,
    ROOM_TV0, 
    ROOM_TV0_CHIMNEYB, 
    ROOM_TV1,
    ROOM_COL345,
    ROOM_WARM_W,
    SINGLE_LED1, SINGLE_LED2, CANDLE1,
    SINGLE_LED1, SINGLE_LED2, SINGLE_LED3) 
Blink2(14, C_RED, SI_1, 400, 150, 0, 100)
Const(14, C_GREEN, SI_1, 0, 40 )
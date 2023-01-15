# Feuerwache rechts mit Turm

## Beschreibung

Längsbau 3x WS2811 + 7x RGB

- linker Flügel
- rechter Flügel
- R=EG rechts G=Eingang B=2OG Giebel
- 5x RGB EG/OG

Turm 3x WS2811 + 3x RGB

- Turm unten
- Turm oben
- R:Warnlicht G:Turmhaus B:Turm unten
- 3 x RGB Turm oben

## MLL Konfiguration

// RGB Balkon + RGB 2 OG
House(1,   SI_1,  4, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M,
    ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W )
House(11,   SI_1,  4, 9, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, SKIP_ROOM,
    ROOM_TV1, ROOM_WARM_W, ROOM_TV1)
Blink2(13, C_RED, SI_1, 300, 1500, 0, 127)
Const(13, C_BLUE, SI_1, 0, 80)
Const(13, C_GREEN, SI_1, 0, 80)
SetLedCount(16)

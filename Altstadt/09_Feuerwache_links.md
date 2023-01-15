# Feuerwache, linker Flügel mit Fahrzeughalle

## Beschreibung

Längsbau 3x WS2811 + 7 RGB

 - R: G: B:
 - R: G: B:
 - R: G: B:
 - 
 -
 -
 -
 -
 - Balkon
 - Dachzimmer

Querbau 4x WS2811, 6x RGB

- Garage Rückseite + Dach, Garage Front 
- 2x3 Hallenbeleuchtung
- Zimmer über Halle (vlnr)

## MLL Konfiguration

```
House(1,   SI_1,  8, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M,  
    ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W ) 

// Zimmer über Garage Innenhof / Dach
House(11,   SI_1,  8, 16, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M, NEON_LIGHT1M, NEON_LIGHT2M, NEON_LIGHT3M)

// Garage
GasLights(13, SI_1, NEON_LIGHT1, NEON_LIGHT2, NEON_LIGHT3, NEON_LIGHT1, NEON_LIGHT2, NEON_LIGHT3) 
  
// 6x RGB (Garage 1 OG Front)
House(15, SI_1, 0, 6, ROOM_TV1, ROOM_TV0, ROOM_TV1, ROOM_WARM_W, ROOM_TV1, ROOM_WARM_W, ROOM_WARM_W ) 
SetLedCount(20)
```
# Bahnsteig Nebenbahn

## Beschreibung

9 RGB LEDs

- Unterführung
- Kiosk
- 7 Deckenleuchten

## MLL Konfiguration

```
// Unterführung
House(1,   SI_1,  1, 1, ROOM_TV1 )
// Kiosk
House(2,   SI_1,  1, 1, ROOM_TV0 ) 
GasLights(3, SI_1, NEON_LIGHTM, NEON_DEF_D, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_LIGHTM, NEON_DEF_D )
SetLedCount(9)
```
# Reiterstellwerk

## Beschreibung

6 RGB LEDs

- Anbau EG hinten
- Einganstüre mit EG vorne
- 2.OG hinten
- 2.OG vorne
- Schaltraum
- Außenlicht (unter Schaltraum)

## MLL Konfiguration

```
HouseT(1, SI_1, 1, 4, 1, 3, ROOM_TV0_CHIMNEYB, ROOM_BRIGHT, ROOM_WARM_W, NEON_LIGHT)
ConstRGB(5 , SI_1, 100, 45, 45, 100, 45, 70)
HouseT(6 ,   SI_1, 0, 1, 5, 35, NEON_LIGHT)
SetLedCount(6)
```
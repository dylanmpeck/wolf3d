-2 = Player Start Position (right now player always begins facing up)

Empty Space:
-1 = Inside (a ceiling will be drawn)
 0 = Outside (skybox will be drawn)

Walls:
1 - Ruin
5 - Jungle
9 - Ice
13 - Bloody

**Each wall has 4 different version which will be displayed based on cardinal direction they face
**These values are loaded as 1-4, 5-9, etc.
**Directions are properly found in the source if initial value is selected.

Doors:
98 = Unlocked Door
99 = Locked Door (Requires key pickup loaded in sprite sheet to open)

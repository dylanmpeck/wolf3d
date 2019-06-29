<h2>Wolf3d</h2>

A classic Wolfenstein 3D clone aimed at learning and reproducing a simple version of John Carmack's raycasting method as well as building a flexible map editor.

<h3>Features</h3>

* Rudimentary 3D graphics achieved through raycasting
* Software rendering by manipulating SDL2 surfaces (hardware rendering was off-limits)
* A maze with varying wall textures based off the cardinal direction that the wall is facing
* Smooth movement
* Wall collision
* Floor, Ceiling, and Skybox
* Decorative, object sprites
* Enemy sprites drawn in 8 different directions
* Random weight based decision making enemy AI
* Very simple gunplay
* Sounds and Music
* Key which can be picked up and used on locked door
* Openable, animated doors
* Simple HUD displaying current health
* Flexible map editor and spritesheet for building more levels

<h3>Compiling and running</h3>

Run make and an executable will be created. Run ./wolf3d path_to_map path_to_spritesheet. Spritesheet is an optional argument.

If the executable fails to run. Try "brew install libmodplug". Only tested on OS X.

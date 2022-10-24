# 42-Cub3d
Simple raycasting engine written entirely in C, with configurable map and wall textures.


## Building
At the root of the repository:

```
make bonus
./cub3d example.cub
```

This compiles and runs the game using an example configuration file.
You can now move through the maze rendered by our raycasing engine and enjoy the animated portal doors, using WASD keys or your mouse.
Press TAB to get a minimap with your current location.

## Config file

The file has to be a textfile with extesion ```.cub```

The first four lines are the wall textures, one for every orientation:
* SO the textures for the south exposed walls
* WE for the ones exposed to west
* EA the eastern ones
* NO the north facing walls

Example:
```SO <valid path to an .xpm image> <\n> ```

Lines preceded by ```F``` are arsed as RGB values for the floor color, lines preceeded by ```C``` are decoded as ceiling color.

The map follows. It has to be free of newlines, ```0``` encodes walkable space, ```1``` a wall, Space a void in the map. All walkable sapces have to be enclosed by walls.
A capital letter, ```N```, ```E```, ```S``` or ```W```, placed in a walkable aread, encodes the spawnpoint of the player and its initial geographical facing direction.

Have fun building the most itricated maze!

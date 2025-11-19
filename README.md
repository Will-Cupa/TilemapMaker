# TilemapMaker
A tool to make tilemaps for game levels based off any tileset provided by the user.

## setup

### Linux/Unix
To setup your environment for the project just run :

```sh
sudo ./setup_dev.sh
```
This will install all dependencies and compile a first time.
Run it and you're good to go !

### Windows
First install all dependencies listed in [dependencies](#dependencies).

Make sure you have both header files and lib files. 

Last but not least, put SDL2.dll in your ./bin folder (or where you will put your executable after compilation). 

## Compile

### Linux/Unix
```sh
g++ src/*.cpp `sdl2-config --cflags --libs` -lSDL2_image -o bin/main
```

### Windows
```sh
g++ src/*.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL_image -o bin/main

g++ src/*.cpp -IZ:\personal\SDL2Library\include -LZ:\personal\SDL2Library\lib -lmingw32 -lSDL2main -lSDL2 -o bin/main
```

## Library
Made in C++ with SDL.

## Dependencies
- SDL2
- SDL2_image


sudo apt-get install libsdl2-dev
dpkg -L libsdl2-dev | grep SDL.h

sudo apt-get install libsdl2-image-dev
dpkg -L libsdl2-image-dev | grep SDL.h

mkdir -p bin

echo "Compiling"
g++ src/*.cpp `sdl2-config --cflags --libs` -lSDL2_image -o bin/main
echo "Compiled"
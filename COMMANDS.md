### make

#### In Windows console

##### Compile for windows (command-prompt)
docker run --rm -v "%cd%:/app" -w /app minextu/sdl2-cross-platform make

##### Compile for linux
docker run --rm -v "%cd%:/app" -w /app minextu/sdl2-cross-platform make -- OS=Linux

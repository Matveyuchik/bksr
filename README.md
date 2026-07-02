**B**asic **K**ool **S**olid **R**aycast is the simple pseudo-3D raycast engine, written in C.

# Features
1. DDA-algorithm for rendering
2. Audio playback
3. Map system

# Build
Install `cmake`, `make` and `gcc` if you haven't installed yet. Also make sure you have installed `glfw3`

Then create a `build` directory:
```bash
mkdir build && cd build
```
then start `cmake`:
```bash
cmake ..
```
and finally, just run `make`:
```bash
make
```
Voila. Now you have `./bksr` executable that you can execute.

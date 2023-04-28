# Triangle Game 2.0


This is a clone of the Triangle Game from [Cracker Barrel](https://blog.crackerbarrel.com/2021/08/13/how-to-beat-the-cracker-barrel-peg-game/).

I have been fascinated by this game for many years, and attempted to [create a solver](https://github.com/jamesraylittle/Triangle-Game) several years ago to practice my C++ during my years in college. I never finished it, so this project serves to revisit that project.

## Building

This project uses `CMake` as the meta build system.

An "out of source" build is recommended. In order to build out of source run the following commands:

```bash
mkdir -p build
cmake -S ../src -B .
```

However, a script has been provided to automate this process. The build script accepts two optional arguments:
1. The build directory
2. The source directory

The script also can provide flags to `CMake` and `Make` by seeting the environment variables `ANY_CFLAGS` and `ANY_MAKEFLAGS` respectively.

To build the project, with the script, run the following command:

```bash
./build.sh
```

After building the project, the executable will be located in the `build` directory, under the game directory, named `triganle-game`.

## Goals
* ✅ Implement a Build system (ninja, cmake)
* ✅ Implement Basic Game Mechanics
* ☑️ Implement a program arguments
* ☑️ Implement some sort of inter-process communication for a game solver
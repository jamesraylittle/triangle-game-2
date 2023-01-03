# Triangle Game 2.0


This is a clone of the Triangle Game from [Cracker Barrel](https://blog.crackerbarrel.com/2021/08/13/how-to-beat-the-cracker-barrel-peg-game/).

I have been fascinated by this game for many years, and attempted to [create a solver](https://github.com/jamesraylittle/Triangle-Game) several years ago to practice my C++ during my years in college. I never finished it, so this project serves to revisit that project.

## Technical Details

This project uses `C++17`, currently there is no meta build system.

In order to compile currently, run:
`g++ main.cpp board.cpp -o main --std=c++17`

#### Goals
* Implement a Build system (ninja, cmake)
* Implement Basic Game Mechanics
* Implement some sort of inter-process communication for a game solver
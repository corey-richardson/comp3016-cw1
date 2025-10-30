# COMP3016 CW1

Immersive Game Technologies

> This is an individual assignment to develop a 2D game in C++. <br>
> Implement a 2D game in C++ and upload to your git repository, then share the link in the readme. Your game needs to adhere to OOP concepts and additionally be able to load file content during execution. Do enough documented testing that it can be built and compile, and that it doesn’t crash upon unexpected input. Lastly, add in as many features as you can to make it story rich and/or fun!

[![wakatime](https://wakatime.com/badge/user/55c30436-1509-4eb9-9f18-fa9b7c6060c4/project/0ae22791-78f9-4b74-a85d-f959b47d3de3.svg)](https://wakatime.com/badge/user/55c30436-1509-4eb9-9f18-fa9b7c6060c4/project/0ae22791-78f9-4b74-a85d-f959b47d3de3)

| YouTube Game Demonstration and Code Walkthrough Link |
| :---: |
|  |
<!-- TODO -->

---

## Contents

1. [Gameplay Description](#gameplay-description)  
2. [Dependencies Used](#dependencies-used)  
3. [Use of AI Description](#use-of-ai-description)  
4. [Game Programming Patterns Used](#game-programming-patterns-used)  
5. [Game Mechanics and How They Are Coded](#game-mechanics-and-how-they-are-coded)  
6. [UML Design Diagrams](#uml-design-diagrams)  
7. [Sample Screens](#sample-screens)  
8. [Exception Handling and Test Cases](#exception-handling-and-test-cases)  
9. [Further Details](#further-details)  
10. [Project Evaluation](#project-evaluation)

## Gameplay Description

"Puzzle Path Game" is a tile based puzzle game where the player must use logic and reasoning skills to navigate a grid, visiting every walkable tile on their way.

The objective of the same is to move from the Start `S` tile to the End `E` tile, visiting every walkable tile on their route. If the user reaches the End `E` tile without first visiting every walkable tile, the level is considered to be in an unsolvable condition and the level is reset to it's initial state.

The game is inspired by B-Cubed on CoolMathsGames, an educational games platform. The game develops skills in younger players including logic, spatial reasoning and forward planning. The design of the game encourages players to reason through sequences and visualise the route in their minds before making a move.

The game features two main walkable tile types: Walkable `#` and Multi-Visit `2`, `1`. Whereas Walkable tiles may only be visited once, Multi-Visit tiles mist be visited multiple times before they are considered 'visited' by the game engine. This adds a layer of complexity and depth to the planning, where a tile will need to be revisited again later in the solution sequence. This complexity is introduced gradually in the Standard mode of the game, forcing the player to problem-solve and reason to understand the new mechanism.

There are two modes for gameplay, selectable in the Main Menu screen of the game.

Standard:
- Levels are played in a set sequential order as listed in the [level manifest file](./app/levels/level-manifest.txt), introducing complexity gradually.

Endless Random Mode:
- Levels are randomly shuffled each play-through cycle allowing for infinite replayability, with a running counter to track the progres of total levels completed across cycles.

## Dependencies Used

The project uses standard C++ libraries:
- `iostream`, `string`, `vector` Core utility.
- `fstream` File I/O for runtime level loading handling.
- `random`, `chrono`, `algorithm` Used by the `RandomGame` class to `std::shuffle` the level sequences, a time-based seed is used for randomisation.
- `memory` Used by `std::unique_ptr` to handle resource management for polymorphic `Game` and `RandomGame` objects, and dynamic safe memory allocation for `Grid` and `PlayerCursor` objects.

The game also depends on level files being present in `.txt` format in a `levels/` directory alongside the program's executable file at runtime. 

These files are copied using a Post-Build Event from `./app/levels/` to the output directory at build-time: `Debug/` or `Release/`.

`app` > `Properties` > `Build Events` > `Post-Build Event` > `Command Line`:

```sh
xcopy "$(ProjectDir)levels" "$(TargetDir)levels\" /s /i /y
```

> This command may be required to be changed if building the project on a non-Windows machine.

## Use of AI Description

## Game Programming Patterns Used

## Game Mechanics and How They Are Coded

## UML Design Diagrams

## Sample Screens

## Exception Handling and Test Cases

```txt
PS C:\Users\richa\Desktop\comp3016-cw1\app\x64\Debug> ./app --test
Running in Test Mode.
Loading files from: levels/test-manifest.txt

Loading: tests/test-missing-start.txt
Error Loading Level tests/test-missing-start.txt: Level Load Error: Level failed to initialise: Missing either Start or End tile (Sentinel value check).

Loading: tests/test-missing-end.txt
Error Loading Level tests/test-missing-end.txt: Level Load Error: Level failed to initialise: Missing either Start or End tile (Sentinel value check).

Loading: tests/test-empty.txt
Error Loading Level tests/test-empty.txt: Level Load Error: File contained no level setup data.

Loading: tests/test-invalid-character.txt
Error Loading Level tests/test-invalid-character.txt: Level Load Error: Failed to parse character '! into a Tile.

Loading: tests/test-shape-error.txt
Error Loading Level tests/test-shape-error.txt: Level Load Error: Inconsistent line length in level file tests/test-shape-error.txt

Loading: tests/test-doesnt-exist.txt
Error Loading Level tests/test-doesnt-exist.txt: Level Load Error: Failed to open level file: tests/test-doesnt-exist.txt

Loading: tests/test-skips-to-working.txt
Loaded Level 7
Visit all 3 tiles to pass the level!

P # E

Move (WASD): d

S P E

Move (WASD): d
Level 7 solved!


Loading: tests/test-trailing-newline.txt
Loaded Level 8
Visit all 3 tiles to pass the level!

P # E

Move (WASD): dd

S P E

Move (WASD): Level 8 solved!
```

## Further Details

## Project Evaluation


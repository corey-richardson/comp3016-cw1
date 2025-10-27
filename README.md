# COMP3016 CW1

Immersive Game Technologies

[![wakatime](https://wakatime.com/badge/user/55c30436-1509-4eb9-9f18-fa9b7c6060c4/project/0ae22791-78f9-4b74-a85d-f959b47d3de3.svg)](https://wakatime.com/badge/user/55c30436-1509-4eb9-9f18-fa9b7c6060c4/project/0ae22791-78f9-4b74-a85d-f959b47d3de3)

---

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

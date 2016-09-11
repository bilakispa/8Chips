# 8Chips
A Chip-8 emulator written in C++ using the SDL2 multimedia library.
> Chip-8 is a simple, interpreted, programming language which was first used on some do-it-yourself computer systems in the late 1970s and early 1980s. The COSMAC VIP, DREAM 6800, and ETI 660 computers are a few examples.

# To do
* Fix the framerate cap
* Improve `main.cpp`
* Change the audio to a multiplatform solution (`sdl_mixer`)
* Add better error checking and showing on console
* Add console commands
* Add a build

# Usage
(Add how to use the emulator here)

## Input
Chip-8 uses a 16-key hexadecimal keypad, the mapping used is displayed following layout:

**Chip-8 Keypad**

|<kbd>1</kbd>|<kbd>2</kbd>|<kbd>3</kbd>|<kbd>C</kbd>|
|------------|------------|------------|------------|
|<kbd>4</kbd>|<kbd>5</kbd>|<kbd>6</kbd>|<kbd>D</kbd>|
|<kbd>7</kbd>|<kbd>8</kbd>|<kbd>9</kbd>|<kbd>E</kbd>|
|<kbd>A</kbd>|<kbd>0</kbd>|<kbd>B</kbd>|<kbd>F</kbd>|

**Keyboard**

|<kbd>1</kbd>|<kbd>2</kbd>|<kbd>3</kbd>|<kbd>4</kbd>|
|------------|------------|------------|------------|
|<kbd>Q</kbd>|<kbd>W</kbd>|<kbd>E</kbd>|<kbd>R</kbd>|
|<kbd>A</kbd>|<kbd>S</kbd>|<kbd>D</kbd>|<kbd>F</kbd>|
|<kbd>Z</kbd>|<kbd>X</kbd>|<kbd>C</kbd>|<kbd>V</kbd>|

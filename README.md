# Non-Intersecting Chess Layouts
## Introduction
Have you ever wonderded how many queens or rooks is it possible to place on a chessboard without their moves conflicting?
With this simple program you can find out.

This program was a part of my undergraduate thesies project: https://repozitorij.etfos.hr/islandora/object/etfos%3A3370

## How to use
1. Press `start.exe`
2. Input board size (Smaller boards will take shorter time to execute)
3. Input chess pieces
4. There are 3 buttons which will display non-intersecting chess layouts:
- Display All -> This button will display all possible combinations, for bigger boards it will take forever :)
- Display Fundemental -> This button will display only unique combinations (taking account for rotating and fliping chessboard)
- Display First -> This button will display the first combination it calculates. This is recommended for larger board sizes, you try with 8x8 with 8 queens.
5. Press "Space" to view next combination and "Enter" to finish viewing.
6. In the output window you will then see how many combinations/layouts were shown.

> For developing/debugging build project with `python -m source` for GUI and cmake for the C++ engine (in build/) `cmake .` and `cmake --build .`

## Code Documentation
GUI was developed using CustomTkinter module for Python with PIL for image processing.
Engine was developed in C++ with SFML for showing combinations.

## GUI with Example
### Menu - Dark Theme
![GUI example dark](https://github.com/user-attachments/assets/affb4af0-1224-48e2-802b-766bf9c1a087)
### Menu - Light Theme
![GUI example light](https://github.com/user-attachments/assets/7574efea-88d1-4153-b32a-1656fa711427)
### Layout Example
![layout example](https://github.com/user-attachments/assets/6816780d-e34c-4a45-93e3-fe4c80ba757f)

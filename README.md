# Minesweeper C Code
This is a simple implementation of the classic game Minesweeper in C. The game is played on a 10x10 grid and the player's goal is to uncover all cells that do not contain a mine.

# How to Play
The player is prompted to enter a command and a cell's row and column. The command can be either 'c' for check cell or 'f' for flag cell.

'c' command: This command is used to uncover a cell. If the cell contains a mine, the game is over. If the cell does not contain a mine, it displays the number of adjacent cells that contain mines.

'f' command: This command is used to flag a cell that the player believes contains a mine.

The game continues until all cells that do not contain mines are uncovered or a cell containing a mine is uncovered.

# Code Structure
The code is structured around several key functions:

printGrid(): This function prints the current state of the game grid.

check(int, int): This function uncovers a cell at the given row and column.

flag(int, int): This function flags a cell at the given row and column.

checkWin(): This function checks if the win conditions are met (all cells that do not contain mines are uncovered).

countAdjacent(char [10][10], int, int): This function counts the number of mines adjacent to a cell.

withinArray(int , int): This function checks that an index is within the array.

# Compilation
To compile the code, use the following command:

gcc -o minesweeper minesweeper.c  

To run the game, use the following command:

./minesweeper  

Enjoy the game!

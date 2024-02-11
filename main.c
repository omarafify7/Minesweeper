#include <stdio.h>
#include <stdlib.h>
#include <time.h>  


//declaring functions
void printGrid();//function that prints the grid
void check (int, int);//function that unlocked a covered position
void flag (int , int );//function that flags a covered position
int checkWin ();//checks to see if win conditions are met
int countAdjacent(char [10][10], int, int);//functions that counts the number of mines adjacent to a cell
int withinArray(int , int);//function that checks that an index is within the array
void handleUserInput(char* command, int* userRow, int* userCol);
void updateGameState(char command, int userRow, int userCol);
void initializeGame();

//declaring variables that will be used later in the program, some of these need to be global because they will be referenced in functions outside the main
int row = 10, col = 10, lockedCells = 0, continuePlaying = 0;
char coveredArray[10][10];
char completeArray[10][10];
char command;

int main(void)
{
    initializeGame();

    char command;
    int userCol, userRow;
    while(!continuePlaying){//continuePlaying is originally 0 which equals false, so !false = true
        printGrid();//printing the grid
        handleUserInput(&command, &userRow, &userCol);  
        updateGameState(command, userRow, userCol);  
    }
}

//defining functions

void printGrid(){
    for(int i = 0; i < 10; i++) {//looping through the entire array
        for (int j = 0; j < 10; j++) {
            printf("%c  ", coveredArray[i][j]);//printing the value at the index from the loop
        }
        printf("\n");//goes to a new line once 10 spots are printed
    }
}

int countAdjacent(char uncoveredArray[10][10], int i, int j){
    int count = 0, x, y;//setting the count value to 0. x and y will represent the new index positions
    int offset[8][2] = {//this array stores the difference in index value for all surrounding cells like N,E,W,S,NE,NW,SW,SE
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}
    };
    for (int k = 0; k < 8; k++){//there are up to 8 surrounding cells
        x = i + offset[k][0];//adds the difference for the row index
        y = j + offset[k][1];//adds the difference for the column index
        int valid = withinArray(x, y);//checks if the new x and y indices are within the array. If its within, it returns 1 which = true
        if (valid){
            if (uncoveredArray[x][y] == 'M')//if a mine is found, the counter increases by 1
                count++;
        }
    }
    return count;//returns the number of adjacent mines
}

int withinArray(int x, int y){
    if ((x >= 0 && x < row) && (y >= 0 && y < col))//returns 1 if the row and column is within the array's dimensions
        return 1;
    return 0;//otherwise returns 0
}

void flag (int thisRow, int thisCol){
    if(coveredArray[thisRow][thisCol] == '*')//if the value at the index is a * then it will flag it
        coveredArray[thisRow][thisCol] = 'F';//this is needed in case a used flags an already open cell
}

void check (int thisRow, int thisCol){
    if(coveredArray[thisRow][thisCol] != completeArray[thisRow][thisCol]){//if the array the user sees isn't equal to the complete array,
        coveredArray[thisRow][thisCol] = completeArray[thisRow][thisCol];//then set the array the user to have the same value as the complete array at that index
        if(completeArray[thisRow][thisCol] == '0'){//this is where recursion occurs because a '0' means that there are no adjacent miens and more of the board needs to be displayed
            for(int i = thisRow - 1; i <= thisRow + 1; i++){//looping through the adjacent cells
                for(int j = thisCol - 1; j <= thisCol + 1; j++){
                    if(withinArray(i, j))//checks if the index is within the array - when there is a 0 along the border of the array
                        check(i, j);//calls the check function again to displace to update the board in case more 0 are present
                }
            }
            //return 1;//key - complete and hidden = covered
        } else if(completeArray[thisRow][thisCol] == 'M'){//the user opens a mine...
            printGrid();//print the grid
            printf("You hit a mine, game over.\n");//print a losing statement
            continuePlaying = 1;//makes the value of continuePlaying which will make the while loop stop running
        }
    }
}

int checkWin (){
    lockedCells = 0;//resets the value to 0 everytime this function is called
    for(int i = 0; i < 10; i++){//loops through the array
        for(int j = 0; j < 10; j++){
            if(coveredArray[i][j] == '*' || coveredArray[i][j] == 'F')//for every '*' or 'F'
                lockedCells++;//adds 1 to lockedCells
        }
    }
    if(lockedCells == 10) {//if lockedCells is = to exactly 10, this means the user has unlocked all the cells which don't contain mines
        return 1;          //because either the user has flagged all possible mines or flagged some, and unlocked the rest that don't contain mines
    } else
        return 0;//otherwise returns 0 which means the win condition has not been met
}

void handleUserInput(char* command, int* userRow, int* userCol) {  
    printf("Enter 'c' for check cell, 'f' for flag cell.\n"); // prompting the user for input  
    printf("Enter command & cell row col: ");  
    scanf(" %c %d %d", command, userRow, userCol);  
    printf("\n"); // adding the required spacing  
}  

void updateGameState(char command, int userRow, int userCol) {  
    if(command == 'f'){  
        flag(userRow, userCol);  
    } else if(command == 'c'){  
        check(userRow, userCol);  
    }  
    if(checkWin()) { // this is the condition, if met, prints the grid, win statement, and breaks out the while loop  
        printGrid();  
        printf("Congratulations! You win!\n");  
        continuePlaying = 1;  
    }  
} 

void initializeGame(){
    srand(time(NULL));  //seeding the rand function

    //making the covered array
    int mineArray[10][2];//array to made to hold the location (index) of mines
    int rand1;
    int rand2;
    for(int i = 0; i < 10; i++) {
        rand1 = rand() % 10;
        rand2 = rand() % 10;
        if(coveredArray[rand1][rand2] != 'M') {//if the array already is storing a mine at this index,
            coveredArray[rand1][rand2] = 'M';//setting the random index to be a mine
            mineArray[i][0] = rand1;//storing the location of the mines placed in the covered array
            mineArray[i][1] = rand2;
        }else {
            i--;//lower the counter by 1 so that another random position is generated
        }
    }

    //making the cells have the number of neighboring mines
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            completeArray[i][j] = (char) ((int)'0' + countAdjacent(coveredArray, i, j));//the countAdjacent function returns an int type. so, it is added
                                                                                        //to the ASCII value of '0' then converted back to a char
        }
    }

    //filling the array the user will see with "*"
    for(int i = 0; i < 10; i++) {//looping through the whole array
        for (int j = 0; j < 10; j++) {
            coveredArray[i][j] = '*';
        }
    }

    //putting the values of bombs back in because they are overwritten by the countAdjacent function
    for(int i = 0; i < 10; i++){
        completeArray[mineArray[i][0]][mineArray[i][1]] = 'M';//utilizing the stored index value of the mines that was randomly generated
    }
}
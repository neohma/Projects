#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Defining the size of the board
#define BOARD_SIZE 4

// Function to check whether 2 and 4 are present or not
int present24(int board[BOARD_SIZE][BOARD_SIZE])
{

    int flag2 = 0, flag4 = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {

            if (board[i][j] == 2)   // If 2 is present set flag2 as 1 and break loop  					      // Also check if 4 is present in the board set flag4 as 1 and break loop

                flag2 = 1;

            else if (board[i][j] == 4)

                flag4 = 1;

        }

        if (flag2 == 1 && flag4 == 1)    // If both flags are equal to one return true

            return 1;

    }

    return 0;

}

// Function to generate a random number
int generateRandomNumber(int board[BOARD_SIZE][BOARD_SIZE])
{

    int i, j;        // Variable to store the row and column number  				   // Variable that stores the random number generated

    int num1 = 2; // Generate number 2
    int num2 = 4; // Generate number 4


    while (1) {

        i = rand() % BOARD_SIZE;     // Generate a random row index for the board array

        j = rand() % BOARD_SIZE;     // Generate a random column index for the board array

        if (board[i][j] == 0) {      // If the position is empty then break from loop

            board[i][j] = num1, num2;       // Set the random number in the board

            break;

        }

    }

    return 0;

}

// Function to print the board
void printBoard(int board[BOARD_SIZE][BOARD_SIZE])
{

    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {

            printf("%d\t", board[i][j]);      // Print the values in the board  				           // Put a tab after printing each element

        }

        printf("\n");       // After printing one row go to next line

    }

}

// Function to check if game is over or not
int gameOver(int board[BOARD_SIZE][BOARD_SIZE])
{

    int flag = 1;      // Variable to check if game is over or not  				      // Variable to count the number of empty spaces in the board

    int count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {

            if (board[i][j] == 0)       // If the board has any empty space set flag as 0 and increment count  				              // Check if any adjacent elements are equal

                flag = 0, count++;

            if (i != BOARD_SIZE - 1) {

                if (board[i][j] == board[i + 1][j])   // Check the element below the current element

                    flag = 0;

            }

            if (j != BOARD_SIZE - 1) {
                if (board[i][j] == board[i][j + 1])   // Check the element right to the current element
                    flag = 0;
            }
        }
    }
    if (flag == 1 && count == 0)      // If flag is one and count is zero return true else false
        return 1;
    else
        return 0;

}

// Function to move the elements up
void moveUp(int board[BOARD_SIZE][BOARD_SIZE])
{

    // Move all the elements up

    for (int j = 0; j < BOARD_SIZE; j++) {

        int k = 0;      // Variable to store the position of the first non-zero element in a column

        for (int i = 0; i < BOARD_SIZE; i++) {

            if (board[i][j] != 0) {     // If current element is non-zero  					      // Swap the current element and first non-zero element in that column

                int temp = board[k][j];

                board[k][j] = board[i][j];

                board[i][j] = temp;

                k++;       // Increment k after each swap

            }

        }
    }
}
// Function to move the elements down
void moveDown(int board[BOARD_SIZE][BOARD_SIZE])
{

    // Move all the elements down

    for (int j = 0; j < BOARD_SIZE; j++) {

        int k = BOARD_SIZE - 1;      // Variable to store the position of the first non-zero element in a column

        for (int i = BOARD_SIZE - 1; i >= 0; i--) {

            if (board[i][j] != 0) {     // If current element is non-zero  					      // Swap the current element and first non-zero element in that column

                int temp = board[k][j];

                board[k][j] = board[i][j];

                board[i][j] = temp;

                k--;       // Decrement k after each swap
            }
        }
    }
}
// Function to move the elements left
void moveLeft(int board[BOARD_SIZE][BOARD_SIZE])
{

    // Move all the elements left

    for (int i = 0; i < BOARD_SIZE; i++) {

        int k = 0;      // Variable to store the position of the first non-zero element in a row

        for (int j = 0; j < BOARD_SIZE; j++) {

            if (board[i][j] != 0) {     // If current element is non-zero  					      // Swap the current element and first non-zero element in that row

                int temp = board[i][k];

                board[i][k] = board[i][j];

                board[i][j] = temp;

                k++;       // Increment k after each swap
            }
        }
    }
}
// Function to move the elements right
void moveRight(int board[BOARD_SIZE][BOARD_SIZE])
{

    // Move all the elements right

    for (int i = 0; i < BOARD_SIZE; i++) {

        int k = BOARD_SIZE - 1;      // Variable to store the position of the first non-zero element in a row

        for (int j = BOARD_SIZE - 1; j >= 0; j--) {

            if (board[i][j] != 0) {     // If current element is non-zero  					      // Swap the current element and first non-zero element in that row

                int temp = board[i][k];

                board[i][k] = board[i][j];

                board[i][j] = temp;

                k--;       // Decrement k after each swap
            }
        }
    }
}
// Function to merge the elements up
int mergeUp(int board[BOARD_SIZE][BOARD_SIZE])
{

    int score = 0;      // Variable to store the score of the game

    for (int j = 0; j < BOARD_SIZE; j++) {

        for (int i = 0; i < BOARD_SIZE - 1; i++) {

            if (board[i][j] != 0 && board[i + 1][j] != 0) {      // If two adjacent elements are non-zero  					      // If both elements are equal, merge them and add the score

                if (board[i][j] == board[i + 1][j]) {

                    board[i][j] *= 2;

                    board[i + 1][j] = 0;

                    score += board[i][j];
                }
            }
        }
    }
    return score;
}
// Function to merge the elements down
int mergeDown(int board[BOARD_SIZE][BOARD_SIZE])
{

    int score = 0;      // Variable to store the score of the game

    for (int j = 0; j < BOARD_SIZE; j++) {

        for (int i = BOARD_SIZE - 1; i > 0; i--) {

            if (board[i][j] != 0 && board[i - 1][j] != 0) {      // If two adjacent elements are non-zero  					      // If both elements are equal, merge them and add the score

                if (board[i][j] == board[i - 1][j]) {

                    board[i][j] *= 2;

                    board[i - 1][j] = 0;

                    score += board[i][j];
                }
            }
        }
    }
    return score;
}
// Function to merge the elements left
int mergeLeft(int board[BOARD_SIZE][BOARD_SIZE])
{

    int score = 0;      // Variable to store the score of the game

    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE - 1; j++) {

            if (board[i][j] != 0 && board[i][j + 1] != 0) {      // If two adjacent elements are non-zero  					      // If both elements are equal, merge them and add the score

                if (board[i][j] == board[i][j + 1]) {

                    board[i][j] *= 2;

                    board[i][j + 1] = 0;

                    score += board[i][j];
                }
            }
        }
    }
    return score;
}
// Function to merge the elements right
int mergeRight(int board[BOARD_SIZE][BOARD_SIZE])
{

    int score = 0;      // Variable to store the score of the game

    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = BOARD_SIZE - 1; j > 0; j--) {

            if (board[i][j] != 0 && board[i][j - 1] != 0) {      // If two adjacent elements are non-zero  					      // If both elements are equal, merge them and add the score

                if (board[i][j] == board[i][j - 1]) {

                    board[i][j] *= 2;

                    board[i][j - 1] = 0;

                    score += board[i][j];
                }
            }
        }
    }
    return score;
}
// Function to move the elements and merge them
int moveAndMerge(int board[BOARD_SIZE][BOARD_SIZE], char direction)
{

    int score = 0;      // Variable to store the score of the game

    if (direction == 'w') {      // If direction is up, call moveUp and mergeUp functions

        moveUp(board);

        score += mergeUp(board);

        moveUp(board);

    } else if (direction == 's') {      // If direction is down, call moveDown and mergeDown functions  				      // Similarly for other directions call appropriate functions

        moveDown(board);

        score += mergeDown(board);

        moveDown(board);

    } else if (direction == 'a') {

        moveLeft(board);

        score += mergeLeft(board);

        moveLeft(board);

    } else if (direction == 'd') {

        moveRight(board);

        score += mergeRight(board);

        moveRight(board);
    }
    return score;
}
// Function to save the game data
void saveData(int board[BOARD_SIZE][BOARD_SIZE], int score)
{

    FILE *file;      // Pointer to the file  				      // Open the file in append mode

    file = fopen("board.txt", "a");

    fprintf(file, "%d\n", score);     // Append the score in the next line of the file

    for (int i = 0; i < BOARD_SIZE; i++) {       // Write the board values in next four lines of the file

        for (int j = 0; j < BOARD_SIZE; j++) {

            fprintf(file, "%d ", board[i][j]);
        }

        fprintf(file, "\n");
    }
    printf("Game Saved Successfully!\n");      // Print success message

    fclose(file);     // Close the file
}

// Function to load the game data
void loadData(int board[BOARD_SIZE][BOARD_SIZE], int *score)
{

    FILE *file;      // Pointer to the file  				      // Open the file in write mode

    file = fopen("board.txt", "r");

    fscanf(file, "%d\n", score);     // Read the score from first line of the file

    for (int i = 0; i < BOARD_SIZE; i++) {       // Read the board values from next four lines of the file

        for (int j = 0; j < BOARD_SIZE; j++) {

            fscanf(file, "%d ", &board[i][j]);
        }
    }
    printf("Game Loaded Successfully!\n");      // Print success message

    fclose(file);     // Close the file
}

void writeToFile(int board[BOARD_SIZE][BOARD_SIZE])
{
    FILE *fp;
    fp = fopen("board.txt", "w");
    for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                fprintf(fp, "%d\t", board[i][j]);
            }
            fprintf(fp, "\n");
        }
            fclose(fp);
}

void readFromFile(int board[BOARD_SIZE][BOARD_SIZE])
{
    FILE *fp;
    fp = fopen("board.txt", "r");
    for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                fscanf(fp, "%d\t", &board[i][j]);
            }
        }
            fclose(fp);
}
// Main function

void showLoading() {
    int i;
    for (i = 0; i < 1; i++) {
        printf("Loading...Loadingg...");
        fflush(stdout);
        sleep(1);
        printf("\b\b\b\b    \b\b\b\b");
        fflush(stdout);
        sleep(1);
    }
}

int main() {
    printf("Starting program...\n");

    showLoading();

    printf("\nProgram started!\n");



printf("\n");

char username[10];


    printf("Enter your username: ");
    scanf("%s", username);
    printf("Welcome, %s!\n", username);

    int board[4][4] = {0};      // Initialize the board with zeros
    int score = 0;      // Initialize the score with zero

    // Some code

    while (1) {
        printf("Score: %d\n", score);       // Print the score
        printBoard(board);      // Print the board
        printf("\nEnter 'w' for UP, 's' for DOWN, 'a' for LEFT, 'd' for RIGHT, and 'q' for EXIT: ");     // Ask user to enter a direction
        char direction;     // Variable to store the direction entered by user
        scanf(" %c", &direction);
        if (direction == 'q') {      // If q is pressed, save the game data and break from loop
            saveData(board, score);
            break;
        } else {      // Else move elements in the given direction and merge them  				      // Generate a new random number in an empty position of the board
            score += moveAndMerge(board, direction);
            generateRandomNumber(board);
        }
        if (gameOver(board) == 1) {      // Check if game is over or not
            printf("Game Over!\n");

            break;
        }
    }

    printf("Final Score: %d\n", score);      // Print the final score of the game
    printf("Username: %s", username);

    return 0;
}



/*
MEMBERS:

Gliponeo, Kurt Russell
Laganas, Andrea
Jarviña, Jhansen Wesley
Subido, Princes Angelie T.
*/


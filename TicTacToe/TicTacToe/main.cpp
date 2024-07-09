#include <iostream>
#include <string>
using namespace std;

const int ROWS = 3;
const int COLS = 3;

void askAboutPlaying();

void runGame();
void initializeGameBoard(string gameBoard[ROWS][COLS]);
void printCurrentBoard(string gameBoard[ROWS][COLS]);
void getUserInput(bool &xTurn, string gameBoard[ROWS][COLS]);
void defineWinner(bool xTurn, string gameBoard[ROWS][COLS], string& winner);
bool checkIfEqual(string gameBoard[ROWS][COLS]);

bool cellIsOccupied(int row, int col, string gameBoard[ROWS][COLS]);

int main(int argc, const char * argv[]) {
    askAboutPlaying();
    return 0;
}
void askAboutPlaying() {
    string answer = " ";
    while (answer!= "yes") {
        cout << " Would u like to play the game? (yes / no)" << endl;
        cin >> answer;
    }
    runGame();
}
void runGame() {
    string winner = "";
    string gameBoard[ROWS][COLS];
    bool xTurn = true;

    initializeGameBoard(gameBoard);
    printCurrentBoard(gameBoard);

    while (winner == "") {
        if (xTurn) {
            cout << "It's X's turn" << endl;
            getUserInput(xTurn, gameBoard);
            defineWinner(xTurn, gameBoard, winner);
        } else {
            cout << "It's O's turn" << endl;
            getUserInput(xTurn, gameBoard);
            defineWinner(xTurn, gameBoard, winner);
        }
    }

    cout << "Winner is: " << winner << endl;
    askAboutPlaying();
}

void initializeGameBoard(string gameBoard[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = " ";
        }
    }
}

void printCurrentBoard(string gameBoard[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << gameBoard[i][j];
            if (j < COLS - 1) {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < ROWS - 1) {
            cout << "- - - - -" << endl;
        }
    }
    cout << endl;
}

void getUserInput(bool &xTurn, string gameBoard[ROWS][COLS]) {
    int row = 0;
    int col = 0;
    bool keepAsking = true;

    while (keepAsking) {
        cout << "Please enter the row and column (1-3), separated by space: ";
        cin >> row >> col;

        // Adjust user input to array indices (subtract 1)
        row--;
        col--;

        if ((row >= 0 && col >= 0) && (row < ROWS && col < COLS)) {
            if (!cellIsOccupied(row, col, gameBoard)) {
                keepAsking = false;
            } else {
                cout << "Sorry, that cell is already occupied." << endl;
            }
        } else {
            cout << "Invalid input. Please enter row and column numbers between 1 and 3." << endl;
        }
    }

    // Set X or O based on whose turn it is
    if (xTurn) {
        gameBoard[row][col] = "X";
    } else {
        gameBoard[row][col] = "O";
    }

    // Switch turn
    xTurn = !xTurn;

    // Print the updated board
    printCurrentBoard(gameBoard);
}

bool cellIsOccupied(int row, int col, string gameBoard[ROWS][COLS]) {
    return gameBoard[row][col] != " ";
}

void defineWinner(bool xTurn, string gameBoard[ROWS][COLS], string& winner) {
    if (checkIfEqual(gameBoard)) {
        if (xTurn) {
            winner = "O";
        } else {
            winner = "X";
        }
    }
}

bool checkIfEqual(string gameBoard[ROWS][COLS]) {
    // Check rows
    for (int i = 0; i < ROWS; i++) {
        if (gameBoard[i][0] != " " && gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < COLS; j++) {
        if (gameBoard[0][j] != " " && gameBoard[0][j] == gameBoard[1][j] && gameBoard[1][j] == gameBoard[2][j]) {
            return true;
        }
    }

    // Check diagonals
    if (gameBoard[0][0] != " " && gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) {
        return true;
    }
    if (gameBoard[0][2] != " " && gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]) {
        return true;
    }

    return false;
}

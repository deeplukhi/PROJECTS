#include <iostream>
#include <vector>

using namespace std;

bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    // Check if the number is not repeated in the current row
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check if the number is not repeated in the current column
    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check if the number is not repeated in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num; // Make tentative assignment

                        if (solveSudoku(board)) {
                            return true; // Done
                        }

                        board[row][col] = 0; // Undo & try again
                    }
                }
                return false; // This triggers backtracking
            }
        }
    }
    return true; // Puzzle solved
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

void readBoard(vector<vector<int>>& board) {
    cout << "Enter the Sudoku grid (use 0 for empty cells):" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }
}

int main() {
    vector<vector<int>> sudokuGrid(9, vector<int>(9));

    readBoard(sudokuGrid);

    if (solveSudoku(sudokuGrid)) {
        cout << "Sudoku Solved:" << endl;
        printBoard(sudokuGrid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// Maze dimensions
const int N = 10; // Change this for larger/smaller mazes

// Function to print the maze
void printMaze(int maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a cell is valid to move
bool isSafe(int maze[N][N], int x, int y, bool visited[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0 && !visited[x][y]);
}

// DFS function to solve the maze
bool solveMazeUtil(int maze[N][N], int x, int y, int endX, int endY, int sol[N][N], bool visited[N][N]) {
    // If (x, y) is the destination, return true
    if (x == endX && y == endY) {
        sol[x][y] = 1;
        return true;
    }

    // Check if (x, y) is valid
    if (isSafe(maze, x, y, visited)) {
        // Mark (x, y) as part of the solution path
        sol[x][y] = 1;
        visited[x][y] = true;

        // Move right
        if (solveMazeUtil(maze, x, y + 1, endX, endY, sol, visited))
            return true;

        // Move down
        if (solveMazeUtil(maze, x + 1, y, endX, endY, sol, visited))
            return true;

        // Move left
        if (solveMazeUtil(maze, x, y - 1, endX, endY, sol, visited))
            return true;

        // Move up
        if (solveMazeUtil(maze, x - 1, y, endX, endY, sol, visited))
            return true;

        // If none of the moves work, backtrack
        sol[x][y] = 0;
        return false;
    }

    return false;
}

// Function to solve the maze
void solveMaze(int maze[N][N], int startX, int startY, int endX, int endY) {
    int sol[N][N] = {0}; // Solution matrix
    bool visited[N][N] = {false}; // Visited matrix

    // Check if start and end points are valid
    if (!isSafe(maze, startX, startY, visited)) {
        cout << "Invalid starting point!" << endl;
        return;
    }
    if (!isSafe(maze, endX, endY, visited)) {
        cout << "Invalid destination point!" << endl;
        return;
    }

    if (solveMazeUtil(maze, startX, startY, endX, endY, sol, visited)) {
        cout << "Solution Path:" << endl;
        printMaze(sol);
    } else {
        cout << "No solution exists!" << endl;
    }
}

int main() {
    int maze[N][N];

    // Input the maze
    cout << "Enter the maze (" << N << "x" << N << " grid, 0 for path, 1 for wall):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    // Input start and end points
    int startX, startY, endX, endY;
    cout << "Enter the starting point (x y): ";
    cin >> startX >> startY;
    cout << "Enter the destination point (x y): ";
    cin >> endX >> endY;

    // Solve the maze
    solveMaze(maze, startX, startY, endX, endY);

    return 0;
}
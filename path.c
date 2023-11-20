#include <stdio.h>
#include <stdlib.h>

int** readMaze(int* rows, int* cols) {
    int ch, rowCount = 1, colCount = 0, colCopyCnt = 0;

    // Read the maze and determine its dimensions
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch != ' ') {
            colCount++;
        }
    }

    getchar();
    colCopyCnt = colCount;
    colCount = 0;

    // Read the maze again
    rewind(stdin);

    // Allocate memory for the maze
    int** maze = (int**)malloc(rowCount * sizeof(int*));

    // Read the maze from stdin
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            // End of a row, increment rowCount and reset colCount
            rowCount++;

            // Resize the maze array
            maze = (int**)realloc(maze, rowCount * sizeof(int*));

            // Allocate memory for the current row
            maze[rowCount - 1] = (int*)malloc(colCopyCnt * sizeof(int));

            // Reset colCount for the next row
            colCount = 0;
        } else if (ch != ' ') {
            // Resize the current row and add the digit to the maze
            maze[rowCount - 1] = (int*)realloc(maze[rowCount - 1], (colCount + \
1) * sizeof(int));
            maze[rowCount - 1][colCount] = ch - '0';
            colCount++;
        }
    }
    // Set the dimensions
    *rows = rowCount;
    *cols = colCount;

    return maze;
}




// Function to print the maze
void printMaze(int** maze, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", maze[i][j]);
        }
        printf("\n");
    }
}

// Function to free the allocated memory for the maze
void freeMaze(int** maze, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(maze[i]);
    }
    free(maze);
}

// DFS function to find a path from the top-left corner to the bottom-right corner
int dfs(int** maze, int** path, int rows, int cols, int row, int col) {
    // Base cases
    if (row < 0 || col < 0 || row >= rows || col >= cols || maze[row][col] == 0 || pat\
h[row][col] == 1) {
        return 0; // Invalid cell or obstacle, or already visited
    }

    path[row][col] = 1; // Mark the cell as part of the path

    // Check if the current cell is the destination
    if (row == rows - 1 && col == cols - 1) {
        return 1; // Reached the destination
    }

    // Try moving right first
    if (dfs(maze, path, rows, cols, row, col + 1) == 1) {
        return 1;
    }

    // If moving right didn't lead to the destination, try moving down
    if (dfs(maze, path, rows, cols, row + 1, col) == 1) {
        return 1;
    }

    // If neither right nor down leads to the destination, undo the changes
    path[row][col] = 0; // Unmark the cell
    return 0; // No path found from this cell
}

// Function to clear the maze and add back only the 1 values along the correct path
void clearAndAddPath(int** maze, int rows, int cols) {
    // Create a separate array to track the path during DFS traversal
    int** path = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        path[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            path[i][j] = 0;
        }
    }

    // Perform DFS to find the path
    dfs(maze, path, rows, cols, 0, 0);

    // Copy the path back to the original maze array
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j] = path[i][j] == 1 ? 1 : 0;
        }
    }

    // Free the memory allocated for the path
    freeMaze(path, rows);
}

int main() {
    int rows, cols;

    // Read the maze from stdin
    int** maze = readMaze(&rows, &cols);

    // Print the original maze
    printf("Original Maze:\n");
    printMaze(maze, rows, cols);

    // Clear the maze and add back only the 1 values along the correct path
    clearAndAddPath(maze, rows, cols);

    // Print the modified maze
    printf("\nMaze with Only 1 Values Along the Correct Path:\n");
    printMaze(maze, rows, cols);

    // Free the allocated memory
    freeMaze(maze, rows);

    return 0;
}

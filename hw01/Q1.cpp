#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SIZE = 15;

enum CellType {
    WALL,
    PATH,
    ENTRY,
    EXIT
};

struct Cell {
    CellType type;
    bool visited;
};

void generateMaze(std::vector<std::vector<Cell>>& maze) {
    // Initialize maze with walls
    for (int i = 0; i < SIZE; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < SIZE; j++) {
            Cell cell;
            cell.type = WALL;
            cell.visited = false;
            row.push_back(cell);
        }
        maze.push_back(row);
    }

    // Generate random entry and exit positions
    int entryRow = rand() % SIZE;
    int entryCol = 0;
    int exitRow = rand() % SIZE;
    int exitCol = SIZE - 1;

    maze[entryRow][entryCol].type = ENTRY;
    maze[exitRow][exitCol].type = EXIT;

    // Generate maze paths using recursive backtracking algorithm
    std::vector<std::pair<int, int>> stack;
    stack.push_back(std::make_pair(entryRow, entryCol));
    maze[entryRow][entryCol].visited = true;

    while (!stack.empty()) {
        int row = stack.back().first;
        int col = stack.back().second;
        stack.pop_back();

        std::vector<std::pair<int, int>> neighbors;
        if (row > 1 && !maze[row - 2][col].visited) {
            neighbors.push_back(std::make_pair(row - 2, col));
        }
        if (row < SIZE - 2 && !maze[row + 2][col].visited) {
            neighbors.push_back(std::make_pair(row + 2, col));
        }
        if (col > 1 && !maze[row][col - 2].visited) {
            neighbors.push_back(std::make_pair(row, col - 2));
        }
        if (col < SIZE - 2 && !maze[row][col + 2].visited) {
            neighbors.push_back(std::make_pair(row, col + 2));
        }

        if (!neighbors.empty()) {
            stack.push_back(std::make_pair(row, col));

            int randomIndex = rand() % neighbors.size();
            int neighborRow = neighbors[randomIndex].first;
            int neighborCol = neighbors[randomIndex].second;

            maze[neighborRow][neighborCol].visited = true;
            maze[neighborRow][neighborCol].type = PATH;

            int wallRow = (row + neighborRow) / 2;
            int wallCol = (col + neighborCol) / 2;
            maze[wallRow][wallCol].visited = true;
            maze[wallRow][wallCol].type = PATH;

            stack.push_back(std::make_pair(neighborRow, neighborCol));
        }
    }
}

void displayMaze(const std::vector<std::vector<Cell>>& maze) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            switch (maze[i][j].type) {
                case WALL:
                    std::cout << "#";
                    break;
                case PATH:
                    std::cout << ".";
                    break;
                case ENTRY:
                    std::cout << "E";
                    break;
                case EXIT:
                    std::cout << "X";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(0));

    std::vector<std::vector<Cell>> maze;
    generateMaze(maze);

    displayMaze(maze);

    return 0;
}

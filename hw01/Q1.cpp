#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

const int SIZE = 15;
const double WALL_CHANCE = 0.2;

struct Cell
{
    bool visited = false;
    char display = '#';
};

bool IsValid(const vector<vector<Cell>> &maze, int x, int y)
{
    return x > 0 && x < SIZE - 1 && y > 0 && y < SIZE - 1 && !maze[y][x].visited;
}

void GenMaze(vector<vector<Cell>> &maze, int x, int y)
{
    maze[y][x].visited = true;
    maze[y][x].display = (rand() % 100 < WALL_CHANCE * 100) ? '#' : ' ';

    vector<pair<int, int>> directions = {{0, 1}, {-1, 0}, {1, 0}};
    shuffle(directions.begin(), directions.end(), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));

    for (const auto &direction : directions)
    {
        int a = direction.first * 2, e = direction.second * 2;
        int b = x + a, d = y + e;
        int c = x + a / 2, f = y + e / 2;

        if (IsValid(maze, b, d))
        {
            maze[f][c].visited = true;
            maze[f][c].display = (rand() % 100 < WALL_CHANCE * 100) ? '#' : ' ';
            GenMaze(maze, b, d);
        }
    }
}

bool SolveMaze(vector<vector<Cell>> &maze, int x, int y, int prevX, int prevY)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || maze[y][x].display != ' ')
        return false;
    if (y == SIZE - 1)
    {
        maze[y][x].display = '.';
        return true;
    }

    maze[y][x].display = '.';

    vector<pair<int, int>> moves = {{0, 1}, {-1, 0}, {1, 0}};
    for (const auto &move : moves)
    {
        if (move.first != prevX || move.second != prevY)
        {
            if (SolveMaze(maze, x + move.first, y + move.second, -move.first, -move.second))
                return true;
        }
    }

    maze[y][x].display = ' ';
    return false;
}

void PrintMaze(const vector<vector<Cell>> &maze)
{
    for (const auto &row : maze)
    {
        for (const auto &cell : row)
        {
            cout << cell.display;
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<Cell>> maze(SIZE, vector<Cell>(SIZE));
    bool solved = false;

    while (!solved)
    {
        for (auto &row : maze)
        {
            for (auto &cell : row)
            {
                cell.visited = false;
                cell.display = '#';
            }
        }

        default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> distribution(1, SIZE - 2);
        int entryX = distribution(generator);
        maze[0][entryX].display = ' ';

        int exitX = distribution(generator);
        maze[SIZE - 1][exitX].display = ' ';

        GenMaze(maze, entryX, 1);
        solved = SolveMaze(maze, entryX, 0, -1, -1);
    }

    PrintMaze(maze);

    return 0;
}

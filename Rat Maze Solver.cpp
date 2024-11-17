#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define WALL 1
#define PATH 0
#define RAT 'R'
#define EXIT 'E'

using namespace std;

const int MAZE_SIZE = 10;
vector<vector<int>> maze(MAZE_SIZE, vector<int>(MAZE_SIZE));
vector<pair<int, int>> path; 

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void displayMaze(int xRat, int yRat, int xExit, int yExit) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (i == xRat && j == yRat)
                cout << RAT << " ";
            else if (i == xExit && j == yExit)
                cout << EXIT << " ";
            else if (maze[i][j] == WALL)
                cout << "# ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void generateRandomMaze() {
    srand(time(0));
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = (rand() % 3 == 0) ? WALL : PATH;
        }
    }
    maze[0][0] = PATH; 
    maze[MAZE_SIZE - 1][MAZE_SIZE - 1] = PATH;
}

bool isValidMove(int x, int y) {
    return x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE && maze[x][y] == PATH;
}

bool solveMaze(int x, int y, int xExit, int yExit) {
    if (x == xExit && y == yExit) {
        path.push_back({x, y}); 
        return true;
    }

    maze[x][y] = WALL; 
    path.push_back({x, y}); 

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isValidMove(newX, newY)) {
            if (solveMaze(newX, newY, xExit, yExit))
                return true;
        }
    }

    path.pop_back(); 
    return false;
}

void displayPath() {
    cout << "Path followed by the rat:\n";
    for (auto p : path) {
        cout << "(" << p.first << ", " << p.second << ") -> ";
    }
    cout << "Exit\n";
}

int main() {
    generateRandomMaze();

    int xRat = 0, yRat = 0;  
    int xExit = MAZE_SIZE - 1, yExit = MAZE_SIZE - 1; 

    displayMaze(xRat, yRat, xExit, yExit);

    if (solveMaze(xRat, yRat, xExit, yExit)) {
        cout << "The rat found a path to the exit!\n";
        displayPath(); 
    } else {
        cout << "No path exists for the rat to reach the exit.\n";
    }

    return 0;
}

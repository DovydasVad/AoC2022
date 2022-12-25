#include <bits/stdc++.h>

using namespace std;

vector<string> readInput() {
    vector <string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

class Cell {
    public:
        int y;
        int x;

        Cell() {}
        Cell(int y_, int x_) {
            y = y_;
            x = x_;
        }

        Cell operator + (const Cell &cell) const {
            return Cell(y + cell.y, x + cell.x);
        }
};

class Blizzard {
    public:
        Cell pos;
        Cell dir;

        Blizzard(Cell pos_, Cell dir_) {
            pos = pos_;
            dir = dir_;
        }

        void moveAndWrap(int n, int m) {
            pos = pos + dir;
            if (pos.y == n - 1) {
                pos.y = 1;
            }
            else if (pos.y == 0) {
                pos.y = n - 2;
            }
            if (pos.x == m - 1) {
                pos.x = 1;
            }
            else if (pos.x == 0) {
                pos.x = m - 2;
            }
        }
};

vector <Blizzard*> initiateBlizzards(vector <string> &maze) {
    int n = maze.size();
    int m = maze.at(0).length();
    vector <Blizzard*> blizzards;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            switch (maze.at(i).at(j)) {
                case '>':
                    blizzards.push_back(new Blizzard(Cell(i, j), Cell(0, 1)));
                    break;
                case 'v':
                    blizzards.push_back(new Blizzard(Cell(i, j), Cell(1, 0)));
                    break;
                case '<':
                    blizzards.push_back(new Blizzard(Cell(i, j), Cell(0, -1)));
                    break;
                case '^':
                    blizzards.push_back(new Blizzard(Cell(i, j), Cell(-1, 0)));
                    break;
                default:
                    break;
            }
        }
    }
    return blizzards;
}

void initiateFields(int n, int m, vector <vector <bool>> &blizzardPositions, vector <vector <bool>> &reachablePositions, vector <vector <bool>> &nextReachablePositions) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            blizzardPositions[i][j] = false;
            reachablePositions[i][j] = nextReachablePositions[i][j];
            nextReachablePositions[i][j] = false;
        }
    }
}

void makeMove(int y, int x, vector <string> &maze, vector <vector <bool>> &blizzardPositions, vector <vector <bool>> &nextReachablePositions) {
    if (blizzardPositions[y][x] == false) {
        nextReachablePositions[y][x] = true;
    }
    if (y > 0 && blizzardPositions[y - 1][x] == false && maze[y - 1][x] != '#') {
        nextReachablePositions[y - 1][x] = true;
    }
    if (y < maze.size() - 1 && blizzardPositions[y + 1][x] == false && maze[y + 1][x] != '#') {
        nextReachablePositions[y + 1][x] = true;
    }
    if (blizzardPositions[y][x - 1] == false && maze[y][x - 1] != '#') {
        nextReachablePositions[y][x - 1] = true;
    }
    if (blizzardPositions[y][x + 1] == false && maze[y][x + 1] != '#') {
        nextReachablePositions[y][x + 1] = true;
    }
}

void traverseMaze(Cell start, Cell end, vector <string> &maze, vector <Blizzard*> &blizzards, int &turn) {
    int n = maze.size();
    int m = maze.at(0).length();
    vector <vector <bool>> reachablePositions(n, vector <bool>(m)), nextReachablePositions(n, vector <bool>(m)), blizzardPositions(n, vector <bool>(m));
    
    nextReachablePositions[start.y][start.x] = true;

    bool endReached = false;
    while (!endReached) {
        turn++;
        initiateFields(n, m, blizzardPositions, reachablePositions, nextReachablePositions);
        for (int i = 0; i < blizzards.size(); i++) {
            blizzards.at(i)->moveAndWrap(n, m);
            blizzardPositions[blizzards.at(i)->pos.y][blizzards.at(i)->pos.x] = true;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (reachablePositions[i][j] == true) {
                    makeMove(i, j, maze, blizzardPositions, nextReachablePositions);
                }
            }
        }

        if (nextReachablePositions[end.y][end.x] == true) {
            endReached = true;
        }
    }
    return;
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> maze = readInput();
    int n = maze.size();
    int m = maze.at(0).length();

    vector <Blizzard*> blizzards = initiateBlizzards(maze);

    int turn = 0;

    traverseMaze(Cell(0, 1), Cell(n - 1, m - 2), maze, blizzards, turn);
    cout << "Part 1: " << turn << endl;

    traverseMaze(Cell(n - 1, m - 2), Cell(0, 1), maze, blizzards, turn);
    traverseMaze(Cell(0, 1), Cell(n - 1, m - 2), maze, blizzards, turn);
    cout << "Part 2: " << turn << endl;
    return 0;
}
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

        Cell() {
            y = 0;
            x = 0;
        }

        Cell(int y_, int x_) {
            y = y_;
            x = x_;
        }

        Cell operator + (Cell &cell) {
            return Cell(y + cell.y, x + cell.x);
        }

        bool operator < (const Cell &cell) const {
            if (y != cell.y) {
                return y < cell.y;
            }
            else {
                return x < cell.x;
            }
        }
};

class Elve {
    public:
        Cell pos;
        Cell moveDir;

        Elve(Cell pos_) {
            pos = pos_;
            moveDir = Cell(0, 0);
        }
};

bool isElveAround(Elve* elve, set <Cell> &elveCoordinates) {
    for (int j = -1; j <= 1; j++) {
        for (int u = -1; u <= 1; u++) {
            Cell dir = Cell(j, u);
            if ((u != 0 || j != 0) && elveCoordinates.find(elve->pos + dir) != elveCoordinates.end()) {
                return true;
            }
        }
    }
    return false;
}

void chooseDirection(deque <vector <Cell>> directions, Elve* elve, map <Cell, int> &cellCounts, set <Cell> &elveCoordinates) {
    for (int j = 0; j < directions.size(); j++) {
        bool directionFree = true;
        for (int u = 0; u < directions.at(j).size(); u++) {
            if (elveCoordinates.find(elve->pos + directions.at(j).at(u)) != elveCoordinates.end()) {
                directionFree = false;
            }
        }
        if (directionFree == true) {
            Cell moveDir = directions.at(j).at(1);
            elve->moveDir = moveDir;
            cellCounts[elve->pos + moveDir]++;
            break;
        }
    }
}

void moveElves(vector <Elve*> &elves, map <Cell, int> &cellCounts, set <Cell> &elveCoordinates) {
    for (int i = 0; i < elves.size(); i++) {
        if (cellCounts[elves.at(i)->pos + elves.at(i)->moveDir] == 1) {
            elveCoordinates.erase(elveCoordinates.find(elves.at(i)->pos));
            elves.at(i)->pos = elves.at(i)->pos + elves.at(i)->moveDir;
            elveCoordinates.insert(elves.at(i)->pos);
        }
    }
}

int getRectangleArea(vector <Elve*> &elves) {
    int minX = 2000000, maxX = -2000000, minY = 2000000, maxY = -2000000;

    for (int i = 0; i < elves.size(); i++) {
        minX = min(minX, elves.at(i)->pos.x);
        maxX = max(maxX, elves.at(i)->pos.x);
        minY = min(minY, elves.at(i)->pos.y);
        maxY = max(maxY, elves.at(i)->pos.y);
    }

    return (maxX - minX + 1) * (maxY - minY + 1) - elves.size();
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    int n = input.size();
    int m = input.at(0).length();

    vector <Elve*> elves;
    map <Cell, int> cellCounts;
    set <Cell> elveCoordinates;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input.at(i).at(j) == '#') {
                elves.push_back(new Elve(Cell(i, j)));
                elveCoordinates.insert(Cell(i, j));
            }
        }
    }

    vector <Cell> dirN = {Cell(-1, -1), Cell(-1, 0), Cell(-1, 1)}, dirS = {Cell(1, -1), Cell(1, 0), Cell(1, 1)}, dirW = {Cell(-1, -1), Cell(0, -1), Cell(1, -1)}, dirE = {Cell(-1, 1), Cell(0, 1), Cell(1, 1)};
    deque <vector <Cell>> directions = {dirN, dirS, dirW, dirE};

    int turn = 0;
    while (true) {
        cellCounts.clear();
        bool elfMoved = false;
        for (int i = 0; i < elves.size(); i++) {
            elves.at(i)->moveDir = Cell(0, 0);
            if (!isElveAround(elves.at(i), elveCoordinates)) {
                continue;
            }
            elfMoved = true;
            chooseDirection(directions, elves.at(i), cellCounts, elveCoordinates);
        }
        directions.push_back(directions.front());
        directions.pop_front();

        moveElves(elves, cellCounts, elveCoordinates);

        if (turn == 10) {
            cout << "Part 1: " << getRectangleArea(elves) << endl;
        }
        if (!elfMoved) {
            cout << "Part 2: " << turn + 1 << endl;
            break;
        }
        turn++;
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int FIELD_SIZE = 1000, CENTER = FIELD_SIZE / 2, KNOT_COUNT = 9;

vector<string> readInput() {
    vector <string> input;
    string line;
    while(getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

void initField(bool visited[][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            visited[i][j] = false;
        }
    }
    visited[CENTER][CENTER] = true;
}

int countVisitedCells(bool visited[][FIELD_SIZE]) {
    int visitedCount = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            visitedCount += visited[i][j];
        }
    }
    return visitedCount;
}

class Cell {
    public:
        int x;
        int y;

        Cell() {
            x = CENTER;
            y = CENTER;
        }
};

void moveHead(Cell &head, char dir) {
    switch (dir) {
        case 'R':
            head.x++;
            break;
        case 'L':
            head.x--;
            break;
        case 'D':
            head.y++;
            break;
        default:
            head.y--;
            break;
    }
}

void moveTail(Cell &head, Cell &tail) {
    if (tail.x > head.x) {
        tail.x--;
    }
    else if (tail.x < head.x) {
        tail.x++;
    }
    if (tail.y > head.y) {
        tail.y--;
    }
    else if (tail.y < head.y) {
        tail.y++;
    }
}

bool hasToMove(Cell head, Cell previous) {
    return abs(previous.x - head.x) >= 2 || abs(previous.y - head.y) >= 2;
}

int simulateRope(vector <string> &input, int tailKnotCount) {
    bool visited[FIELD_SIZE][FIELD_SIZE];
    initField(visited);
    vector <Cell> body;
    for (int i = 0; i < tailKnotCount; i++) {
        body.push_back(Cell());
    }
    Cell head = Cell();
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input[i];
        char dir;
        int moves;
        ss >> dir >> moves;
        while (moves > 0) {
            moveHead(head, dir);
            for (int j = 0; j < tailKnotCount; j++) {
                int move = 0;
                Cell topKnot = head, currKnot = body.at(j);
                if (j > 0) {
                    topKnot = body.at(j - 1);
                }
                if (hasToMove(topKnot, currKnot)) {
                    moveTail(topKnot, currKnot);
                }
                body.at(j) = currKnot;
            }
            moves--;
            visited[body[tailKnotCount - 1].y][body[tailKnotCount - 1].x] = 1;
        }
    }
    return countVisitedCells(visited);
}

long long part1(vector <string> &input) {
    return simulateRope(input, 1);
}

long long part2(vector <string> &input) {
    return simulateRope(input, 9);
}

void solve(vector <string> input) {
    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
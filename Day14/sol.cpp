#include <bits/stdc++.h>

using namespace std;

const int MAX_X = 1000, MAX_Y = 1000;

vector<string> readInput() {
    vector <string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

void fillIntervals(char cave[][MAX_Y], vector <int> &X1, vector <int> &Y1, vector <int> &X2, vector <int> &Y2) {
    for (int i = 0; i < X1.size(); i++) {
        int y1 = Y1.at(i), x1 = X1.at(i), y2 = Y2.at(i), x2 = X2.at(i);
            if (x1 != -1) {
                if (x1 != x2) {
                    for (int x = min(x1, x2); x <= max(x1, x2); x++) {
                        cave[y1][x] = '#';
                    }
                }
                else {
                    for (int y = min(y1, y2); y <= max(y1, y2); y++) {
                        cave[y][x1] = '#';
                    }
                }
            }
    }
}

void constructCave(vector <string> &input, char cave[][MAX_Y], int &yMax) {
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            cave[i][j] = '.';
        }
    }
    vector <int> X1, Y1, X2, Y2;
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        char comma;
        ss << input.at(i);
        int y1 = -1, x1 = -1, y2 = -1, x2 = -1;
        while (ss >> x2) {
            ss >> comma >> y2;
            yMax = max(yMax, y2);
            X1.push_back(x1);
            Y1.push_back(y1);
            X2.push_back(x2);
            Y2.push_back(y2);
            x1 = x2;
            y1 = y2;
            string arrow;
            if (ss.rdbuf()->in_avail() != 0)
                ss >> arrow;
        }
    }
    fillIntervals(cave, X1, Y1, X2, Y2);
}

void clearCave(char cave[][MAX_Y]) {
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (cave[i][j] == 'O') {
                cave[i][j] = '.';
            }
        }
    }
}

pair <int, int> fillABlock(char cave[][MAX_Y]) {
    int I = 0, J = 500;
    while (I < MAX_Y - 1) {
        if (cave[I + 1][J] == '.') {
            I++;
        }
        else if (cave[I + 1][J - 1] == '.') {
            I++;
            J--;
        }
        else if (cave[I + 1][J + 1] == '.') {
            I++;
            J++;
        }
        else {
            break;
        }
    }
    if (I >= MAX_Y - 1 || (I == 0 && J == 500)) {
        return {-1, -1};
    }
    cave[I][J] = 'O';
    return {I, J};
}

long long part1(char cave[][MAX_Y], int yMax) {
    bool pouring = true;
    int sandCount = 0;
    while (pouring) {
        sandCount++;
        pair <int, int> newBlock = fillABlock(cave);
        if (newBlock.first == -1) {
            pouring = false;
        }
    }
    return sandCount - 1;
}

long long part2(char cave[][MAX_Y], int yMax) {
    clearCave(cave);
    bool pouring = true;
    int sandCount = 0;
    yMax += 2;
    for (int x = 0; x < MAX_X; x++) {
        cave[yMax][x] = '#';
    }
    while (pouring) {
        sandCount++;
        pair <int, int> newBlock = fillABlock(cave);
        if (newBlock.first == -1) {
            pouring = false;
        }
    }
    return sandCount;
}

void solve(vector <string> input) {
    char cave[MAX_Y][MAX_X];
    int yMax = 0;
    constructCave(input, cave, yMax);
    cout << "Part 1: " << part1(cave, yMax) << endl;
    cout << "Part 2: " << part2(cave, yMax) << endl;
}

char cave[MAX_Y][MAX_X];

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
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

void parseInput(vector <string> &input, vector <int> &sensorX, vector <int> &sensorY, vector <int> &closestX, vector <int> &closestY) {
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input[i];
        string s;
        char c;
        int sx, sy, bx, by;
        ss >> s >> s >> c >> c >> sx >> c >> c >> c >> sy >> c >> s >> s >> s >> s >> c >> c >> bx >> c >> c >> c >> by;
        sensorX.push_back(sx);
        sensorY.push_back(sy);
        closestX.push_back(bx);
        closestY.push_back(by);
    }
}

vector <pair <int, int>> makeIntervals(vector <int> &sensorX, vector <int> &sensorY, vector <int> &closestX, vector <int> &closestY, long long &count, long long yQuery) {
    vector <pair<int, int>> emptyIntervals;
    set <int> existingX;
    for (int i = 0; i < sensorX.size(); i++) {
        int manhatanDist;
        if (closestY.at(i) == yQuery && existingX.find(closestX.at(i)) == existingX.end()) {
            count--;
            existingX.insert(closestX.at(i));
        }
        manhatanDist = abs(sensorX.at(i) - closestX.at(i)) + abs(sensorY.at(i) - closestY.at(i));
        int dy = abs(yQuery - sensorY.at(i));
        if (dy <= manhatanDist) {
            int l, r;
            l = sensorX.at(i) - (manhatanDist - dy);
            r = sensorX.at(i) + (manhatanDist - dy);
            emptyIntervals.push_back({l, 1});
            emptyIntervals.push_back({r + 1, -1});
        }
    }
    return emptyIntervals;
}

long long part1(vector <int> &sensorX, vector <int> &sensorY, vector <int> &closestX, vector <int> &closestY) {
    long long count = 0;
    vector <pair<int, int>> emptyIntervals = makeIntervals(sensorX, sensorY, closestX, closestY, count, 2000000);
    sort(emptyIntervals.begin(), emptyIntervals.end());
    int activeIntervals = 0;
    long long intStart = -2000000000;
    for (int i = 0; i < emptyIntervals.size(); i++) {
        int X, status;
        X = emptyIntervals[i].first;
        status = emptyIntervals[i].second;
        activeIntervals += status;
        if (activeIntervals == 1 && status == 1) {
            intStart = X;
        }
        else if (activeIntervals == 0) {
            count += X - intStart;
        }
    }
    return count;
}

long long part2(vector <int> &sensorX, vector <int> &sensorY, vector <int> &closestX, vector <int> &closestY) {
    long long count = 0;
    vector <pair<int, int>> emptyIntervals;
    for (int yQuery = 0; yQuery <= 4000000; yQuery++) {
        emptyIntervals = makeIntervals(sensorX, sensorY, closestX, closestY, count, yQuery);
        sort(emptyIntervals.begin(), emptyIntervals.end());
        int active = 0;
        long long intervalStart = -2000000000;
        for (int i = 0; i < emptyIntervals.size(); i++) {
            int X, status;
            X = emptyIntervals[i].first;
            status = emptyIntervals[i].second;
            active += status;
            if (active == 1 && status == 1) {
                intervalStart = X;
            }
            else if (active == 0) {
                if (i != emptyIntervals.size() - 1 && emptyIntervals[i + 1].first != X) {
                    long long distY = yQuery, distX = X;
                    return 4000000 * distX + distY;
                }
            }
        }
    }
    return -1;
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    vector <int> sensorX, sensorY, closestX, closestY;

    parseInput(input, sensorX, sensorY, closestX, closestY);
    cout << "Part 1: " << part1(sensorX, sensorY, closestX, closestY) << endl;
    cout << "Part 2: " << part2(sensorX, sensorY, closestX, closestY) << endl;
    return 0;
}
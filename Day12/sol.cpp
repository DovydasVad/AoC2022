#include <bits/stdc++.h>

using namespace std;

deque <string> readInput() {
    deque <string> input;
    string line;
    while(getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

bool canMove(deque <string> &field, int y, int x, int newY, int newX, string condition) {
    if (condition == "higher") {
        return field[newY][newX] <= field.at(y).at(x) + 1;
    }
    else {
        return field[newY][newX] >= field.at(y).at(x) - 1;
    }
}

int calculateMinimumSteps(int n, int m, deque <string> &field, vector <vector <int>> &steps) {
    int minSteps = 2000000000;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (field[i][j] == 'a' && steps[i][j] != -1) {
                minSteps = min(minSteps, steps[i][j]);
            }
        }
    }
    return minSteps;
}

int traverseField(deque <string> &field, int startY, int startX, int endY, int endX, string condition) {
    int n = field.size();
    int m = field[0].length();
    vector <vector <int>> visited(n, vector <int>(m)), steps(n, vector <int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = 1;
        }
    }
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            visited[i][j] = 0;
            steps[i][j] = -1;
        }
    }
    vector <pair<int,int>> T;
    T.push_back({startY, startX});
    steps[startY][startX] = 0;
    for (int i = 0; i < T.size(); i++) {
        int X, Y;
        Y = T[i].first;
        X = T[i].second;
        if (visited[Y - 1][X] == 0 && canMove(field, Y, X, Y - 1, X, condition)) {
            steps[Y - 1][X] = steps[Y][X] + 1;
            visited[Y - 1][X] = 1;
            T.push_back({Y - 1, X});
        }
        if (visited[Y + 1][X] == 0 && canMove(field, Y, X, Y + 1, X, condition)) {
            steps[Y + 1][X] = steps[Y][X] + 1;
            visited[Y + 1][X] = 1;
            T.push_back({Y + 1, X});
        }
        if (visited[Y][X - 1] == 0 && canMove(field, Y, X, Y, X - 1, condition)) {
            steps[Y][X - 1] = steps[Y][X] + 1;
            visited[Y][X - 1] = 1;
            T.push_back({Y, X - 1});
        }
        if (visited[Y][X + 1] == 0 && canMove(field, Y, X, Y, X + 1, condition)) {
            steps[Y][X + 1] = steps[Y][X] + 1;
            visited[Y][X + 1] = 1;
            T.push_back({Y, X + 1});
        }
    }
    if (condition == "lower") {
        return calculateMinimumSteps(n, m, field, steps);
    }
    else {
        return steps[endY][endX];
    }
}

int main() {
    freopen("input.in", "r", stdin);
    int n, m;
    deque <string> field = readInput();
    n = field.size();
    m = field[0].length();
    string s = "";
    for (int i = 0; i < m + 2; i++) {
        s += '#';
    }
    field.push_back(s);
    field.push_front(s);
    int startY, startX, endY, endX;
    n += 2;
    m += 2;
    for (int i = 1; i < n - 1; i++) {
        field[i] = '#' + field[i] + '#';
        for (int j = 1; j < m - 1; j++) {
            if (field[i][j] == 'S') {
                startY = i;
                startX = j;
            }
            if (field[i][j] == 'E') {
                endY = i;
                endX = j;
            }
        }
    }
    field[startY][startX] = 'a';
    field[endY][endX] = 'z';
    cout << "Part 1: " << traverseField(field, startY, startX, endY, endX, "higher") << endl;
    cout << "Part 2: " << traverseField(field, endY, endX, startY, startX, "lower") << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

vector<string> readInput() {
    vector <string> input;
    string line;
    while(getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

bool isInGrid(int I, int J, int n, int m) {
    return I >= 0 && J >= 0 && I < n && J < m;
}

bool checkVisibility(vector <string> &input, int I, int J, pair <int, int> dir) {
    int n, m, treeHeight;
    n = input.size();
    m = input.at(0).length();
    treeHeight = input[I][J];
    while (isInGrid(I, J, n, m)) {
        I += dir.first;
        J += dir.second;
        if (isInGrid(I, J, n, m) && input[I][J] >= treeHeight) {
            return 0;
        }
    }
    return 1;
}

int getScenicCount(vector <string> &input, int I, int J, pair <int, int> dir) {
    int n, m, treeHeight, currCount = 0;
    n = input.size();
    m = input.at(0).length();
    treeHeight = input[I][J];
    while (isInGrid(I, J, n, m)) {
        I += dir.first;
        J += dir.second;
        currCount++;
        if (isInGrid(I, J, n, m) && input[I][J] >= treeHeight) {
            return currCount;
        }
    }
    return currCount - 1;
}

long long part1(vector <string> &input) {
    int n, m;
    n = input.size();
    m = input.at(0).length();
    int visibleTrees = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < m; j++) {
            if (checkVisibility(input, i, j, {-1, 0}) || checkVisibility(input, i, j, {1, 0}) ||
            checkVisibility(input, i, j, {0, -1}) || checkVisibility(input, i, j, {0, 1})) {
                visibleTrees++;
            }
        }
    }
    return visibleTrees;
}

long long part2(vector <string> &input) {
    int n, m;
    n = input.size();
    m = input.at(0).length();
    int maxScenic = 1;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < m; j++) {
            int scenic = getScenicCount(input, i, j, {-1, 0}) * getScenicCount(input, i, j, {1, 0}) * 
                getScenicCount(input, i, j, {0, -1}) * getScenicCount(input, i, j, {0, 1});
            maxScenic = max(maxScenic, scenic);
        }
    }
    return maxScenic;
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
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

long long getStartMarker(string s, int size) {
    for (int i = 0; i < s.length(); i++) {
        bool isEqual = 1;
        for (int j = 0; j < size; j++) {
            for (int u = 0; u < size; u++) {
                if (j != u && s[i + j] == s[i + u]) {
                    isEqual = 0;
                }
            }
        }
        if (isEqual == 1) {
            return i + size;
        }
    }
    return size + 1;
}

long long part1(vector <string> &input) {
    return getStartMarker(input.at(0), 4);
}

long long part2(vector <string> &input) {
    return getStartMarker(input.at(0), 14);
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
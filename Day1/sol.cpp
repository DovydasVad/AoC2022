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

void precalculate(vector <string> &input, vector <int> &calorieCounts) {
    int calories = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input.at(i) != "") {
            calories += stoi(input.at(i));
        }
        else {
            calorieCounts.push_back(calories);
            calories = 0;
        }
    }
    calorieCounts.push_back(calories);
    sort(calorieCounts.rbegin(), calorieCounts.rend());
}

long long part1(vector <int> &calorieCounts) {
    return calorieCounts.at(0);
}

long long part2(vector <int> &calorieCounts) {
    return calorieCounts.at(0) + calorieCounts.at(1) + calorieCounts.at(2);
}

void solve(vector <string> input) {
    vector <int> calorieCounts;
    precalculate(input, calorieCounts);
    cout << "Part 1: " << part1(calorieCounts) << endl;
    cout << "Part 2: " << part2(calorieCounts) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
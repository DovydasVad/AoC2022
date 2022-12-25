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

long long part1(vector <string> &input) {
    map <pair<char,char>, int> pairToPoints;
    pairToPoints[{'A','X'}] = 4;
    pairToPoints[{'A','Y'}] = 8;
    pairToPoints[{'A','Z'}] = 3;
    pairToPoints[{'B','X'}] = 1;
    pairToPoints[{'B','Y'}] = 5;
    pairToPoints[{'B','Z'}] = 9;
    pairToPoints[{'C','X'}] = 7;
    pairToPoints[{'C','Y'}] = 2;
    pairToPoints[{'C','Z'}] = 6;
    long long Sum = 0;
    for (int i = 0; i < input.size(); i++) {
        char symbolA, symbolB;
        symbolA = input.at(i).at(0);
        symbolB = input.at(i).at(2);
        Sum +=  pairToPoints[{symbolA, symbolB}];
    }
    return Sum;
}

long long part2(vector <string> &input) {
    map <pair<char,char>, int> pairToPoints;
    pairToPoints[{'A','X'}] = 3;
    pairToPoints[{'A','Y'}] = 4;
    pairToPoints[{'A','Z'}] = 8;
    pairToPoints[{'B','X'}] = 1;
    pairToPoints[{'B','Y'}] = 5;
    pairToPoints[{'B','Z'}] = 9;
    pairToPoints[{'C','X'}] = 2;
    pairToPoints[{'C','Y'}] = 6;
    pairToPoints[{'C','Z'}] = 7;
    long long Sum = 0;
    for (int i = 0; i < input.size(); i++) {
        char symbolA, symbolB;
        symbolA = input.at(i).at(0);
        symbolB = input.at(i).at(2);
        Sum +=  pairToPoints[{symbolA, symbolB}];
    }
    return Sum;
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
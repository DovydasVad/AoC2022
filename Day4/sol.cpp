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
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input.at(i);
        int l1, r1, l2, r2;
        char hyphen, comma;
        ss >> l1 >> hyphen >> r1 >> comma >> l2 >> hyphen >> r2;
        if ((l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2)) {
            count++;
        }
    }
    return count;
}

long long part2(vector <string> input) {
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input.at(i);
        int l1, r1, l2, r2;
        char hyphen, comma;
        ss >> l1 >> hyphen >> r1 >> comma >> l2 >> hyphen >> r2;
        if ((l2 <= l1 && l1 <= r2) || (l2 <= r1 && r1 <= r2) || (l1 <= l2 && l2 <= r1) || (l1 <= r2 && r2 <= r1)) {
            count++;
        }
    }
    return count;
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
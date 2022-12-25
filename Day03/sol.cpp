#include <bits/stdc++.h>

using namespace std;

const int PRIORITIES = 52;

vector<string> readInput() {
    vector <string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

int getPriority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    else {
        return c - 'A' + 26;
    }
}

void fillCounts(string s, int counts[]) {
    int n = s.length();
    for (int i = 0; i < PRIORITIES; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        counts[getPriority(s.at(i))]++;
    }
}

long long part1(vector <string> &input) {
    long long ans = 0;
    for (int i = 0; i < input.size(); i++) {
        int counts1[PRIORITIES], counts2[PRIORITIES];
        int n = input.at(i).size();
        fillCounts(input.at(i).substr(0, n/2), counts1);
        fillCounts(input.at(i).substr(n/2, n - (n/2)), counts2);
        for (int j = 0; j < PRIORITIES; j++) {
            if (counts1[j] > 0 && counts2[j] > 0) {
                ans += j + 1;
            }
        }
    }
    return ans;
}

long long part2(vector <string> &input) {
    long long ans = 0;
    for (int i = 0; i < input.size(); i += 3) {
        int counts1[PRIORITIES], counts2[PRIORITIES], counts3[PRIORITIES];
        fillCounts(input.at(i), counts1);
        fillCounts(input.at(i + 1), counts2);
        fillCounts(input.at(i + 2), counts3);
        for (int j = 0; j < PRIORITIES; j++) {
            if (counts1[j] > 0 && counts2[j] > 0 && counts3[j] > 0) {
                ans += j + 1;
            }
        }
    }
    return ans;
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
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

int MAX_LINES = 10;

void processInput(vector <string> &input, deque <char> startingCrates[], vector <int> &boxA, vector <int> &boxB, vector <int> &moveCount) {
    int inputLine;
    for (int i = 0; i < input.size(); i++) {
        if (input[i][1] == '1') {
            inputLine = i + 2;
            break;
        }
        int lane = 1;
        for (int j = 1; j < input[i].length(); j += 4) {
            if (input[i][j] != ' ') {
                startingCrates[lane].push_back(input[i][j]);
            }
            lane++;
        }
    }
    for (int i = inputLine; i < input.size(); i++) {
        int count = input[i][5] - '0';
        int countLength = 1;
        if (input[i][6] != ' ') {
            count = 10 * count + input[i][6] - '0';
            countLength = 2;
        }
        boxA.push_back(input[i][11 + countLength] - '0');
        boxB.push_back(input[i][16 + countLength] - '0');
        moveCount.push_back(count);
    }
}

string part1(deque <char> startingCrates[], vector <int> &boxA, vector <int> &boxB, vector <int> &moveCount) {
    deque <char> crates[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++) {
        crates[i] = startingCrates[i];
    }
    for (int i = 0; i < boxA.size(); i++) {
        for (int j = 0; j < moveCount.at(i); j++) {
            crates[boxB.at(i)].push_front(crates[boxA.at(i)].front());
            crates[boxA.at(i)].pop_front();
        }
    }
    string result = "";
    for (int i = 0; i < MAX_LINES; i++) {
        if (crates[i].size() > 0) {
            result += crates[i].at(0);
        }
    }
    return result;
}

string part2(deque <char> startingCrates[], vector <int> &boxA, vector <int> &boxB, vector <int> &moveCount) {
    deque <char> crates[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++) {
        crates[i] = startingCrates[i];
    }
    for (int i = 0; i < boxA.size(); i++) {
        for (int j = 0; j < moveCount.at(i); j++) {
            crates[boxB.at(i)].push_front(crates[boxA.at(i)][moveCount.at(i)-j-1]);
        }
        for (int j = 0; j < moveCount.at(i); j++) {
            crates[boxA.at(i)].pop_front();
        }
    }
    string result = "";
    for (int i = 0; i < MAX_LINES; i++) {
        if (crates[i].size() > 0) {
            result += crates[i].at(0);
        }
    }
    return result;
}

void solve(vector <string> input) {
    deque <char> startingCrates[MAX_LINES];
    vector <int> boxA, boxB, moveCount;
    processInput(input, startingCrates, boxA, boxB, moveCount);
    cout << "Part 1: " << part1(startingCrates, boxA, boxB, moveCount) << endl;
    cout << "Part 2: " << part2(startingCrates, boxA, boxB, moveCount) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
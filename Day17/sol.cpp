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

bool canBePushed(int I, int J, vector <pair<int, int>> blocks, pair<int, int> dir, vector<char> tower[]) {
    int dx = dir.second;
    int dy = dir.first;
    if (dx == -1 || dx == 1) {
        for (int i = 0; i < blocks.size(); i++) {
            int Y = blocks[i].first + I;
            int X = blocks[i].second + J + dx;
            if (X == -1 || X == 7 || (tower[X].size() - 1 >= Y && tower[X][Y] == '#')) {
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < blocks.size(); i++) {
            int Y = blocks[i].first + I - 1;
            int X = blocks[i].second + J;
            if (tower[X].size() - 1 >= Y && tower[X][Y] == '#') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    string s = input[0];
    int n = s.length(), I, J, charPos = 0;
    int blockCount = 0;
    vector <char> tower[7];
    vector <pair<int, int>> currBlocks, blocks[5];
    int blockHeight[5] = {1, 3, 3, 4, 2}, maxH = 0;
    blocks[0] = {{0,0}, {0,1}, {0,2}, {0,3}};
    blocks[1] = {{-1,0}, {0,1}, {-1,1}, {-1,2}, {-2,1}};
    blocks[2] = {{-2,0}, {-2,1}, {-2,2}, {-1,2}, {0,2}};
    blocks[3] = {{0,0}, {-1,0}, {-2,0}, {-3,0}};
    blocks[4] = {{0,0}, {-1,0}, {0,1}, {-1,1}};
    int thresholdHeight;
    for (int i = 0; i < 7; i++) {
        tower[i].push_back('#');
    }
    vector <long long> heights;
    while (blockCount < 20000) {
        bool fallen = false;
        I = maxH + blockHeight[blockCount % 5] + 3;
        J = 2;
        while (!fallen) {
            int dx = -1;
            if (s[charPos] == '>') {
                dx = 1;
            }
            if (canBePushed(I, J, blocks[blockCount % 5], {0, dx}, tower)) {
                J += dx;
            }
            if (canBePushed(I, J, blocks[blockCount % 5], {-1, 0}, tower)) {
                I--;
            }
            else {
                fallen = true;
                for (int i = 0; i < blocks[blockCount % 5].size(); i++) {
                    int Y = blocks[blockCount % 5][i].first + I;
                    int X = blocks[blockCount % 5][i].second + J;
                    while (tower[X].size() <= Y) {
                        tower[X].push_back('.');
                    }
                    tower[X][Y] = '#';
                    maxH = max(maxH, Y);
                }
            }
            charPos++;
            charPos %= n;
        }
        if (blockCount == 1000) {
            thresholdHeight = maxH;
        }
        if (blockCount > 1000)
            heights.push_back(maxH - thresholdHeight);
        if (blockCount == 2022 - 1) {
            cout << "Part 1: " << maxH << endl;
        }
        blockCount++;
    }
    int prevH = 0;
    for (int i = 0; i < 1600; i++) {
        prevH = heights[i];
    }
    long long cycleLength;
    for (int testCycle = 5; testCycle < 10000; testCycle++) {
        int endValue = heights[testCycle - 1];
        bool valid = true;
        for (int i = testCycle; i < heights.size(); i++) {
            if (heights[i] != (i / testCycle) * endValue + heights[i % testCycle]) {
                valid = false;
                break;
            }
        }
        if (valid == true) {
            cycleLength = testCycle;
            break;
        }
    }
    long long endValue = heights[cycleLength - 1];
    long long index = 1000000000000 - 2;
    long long towerHeight = thresholdHeight + (index - 1000)/cycleLength*endValue + heights[(index - 1000) % cycleLength];
    cout << "Part 2: " << towerHeight << endl;
    return 0;
}
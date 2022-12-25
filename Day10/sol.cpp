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

bool isInterestingTime(int time) {
    return (time + 20) % 40 == 0;
}

void increaseStrength(int &strength, int XValue, int time) {
    if (isInterestingTime(time)) {
        strength += time * XValue;
    }
}

void insertPixel(vector <char> &image, int XValue, int time) {
    time %= 40;
    if (abs(XValue - time) <= 1) {
        image.push_back('X');
    }
    else {
        image.push_back('.');
    }
}

void printImage(vector <char> &image) {
    for (int i = 0; i < image.size(); i++) {
        if (i % 40 == 0) {
            cout << endl;
        }
        cout << image.at(i);
    }
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    int time = 0, XValue = 1, strength = 0;
    set <int> interestingValues = {20, 60, 100, 140, 180, 220};
    vector <char> image;
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input[i];
        string instruction;
        int value;
        ss >> instruction;
        if (instruction == "noop") {
            insertPixel(image, XValue, time);
            time++;
            increaseStrength(strength, XValue, time);
        }
        else {
            ss >> value;
            insertPixel(image, XValue, time);
            time++;
            increaseStrength(strength, XValue, time);
            insertPixel(image, XValue, time);
            time++;
            increaseStrength(strength, XValue, time);
            XValue += value;
        }
    }
    cout << "Part 1: " << strength << endl;
    cout << "Part 2:";
    printImage(image);
    return 0;
}
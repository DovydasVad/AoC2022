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

long long digitToDecimal(char digit) {
    switch (digit) {
        case '=':
            return -2;
        case '-':
            return -1;
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        default:
            return 0;
    }
}

char digitToSnafu(int digit) {
    switch (digit) {
        case 3:
            return '=';
        case 4:
            return '-';
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        default:
            return '#';
    }
}

long long toDecimal(string snafu) {
    long long digitValue = 1, number = 0;
    for (int i = snafu.length() - 1; i >= 0; i--) {
        number += digitValue * digitToDecimal(snafu.at(i));
        digitValue *= 5;
    }
    return number;
}

string toSnafu(long long decimal) {
    string snafu = "";
    while (decimal > 0) {
        int digit = decimal % 5;
        char snafuDigit = digitToSnafu(digit);
        snafu = digitToSnafu(digit) + snafu;
        if (snafuDigit == '-') {
            decimal++;
        }
        else if (snafuDigit == '=') {
            decimal += 2;
        }
        decimal /= 5;
    }
    return snafu;
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    long long sum = 0;
    for (int i = 0; i < input.size(); i++) {
        sum += toDecimal(input.at(i));
    }
    cout << "Part 1: " << toSnafu(sum) << endl;
    return 0;
}
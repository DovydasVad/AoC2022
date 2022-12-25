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

class MonkeyData {
    public:
        deque <deque <long long>> startItems;
        vector <char> op;
        vector <long long> op2;
        vector <long long> test;
        vector <long long> monkeyA;
        vector <long long> monkeyB;

        MonkeyData(int n) {
            startItems = deque <deque <long long>>(n, deque <long long>(0));
            op = vector <char>(n);
            op2 = vector <long long>(n);
            test = vector <long long>(n);
            monkeyA = vector <long long>(n);
            monkeyB = vector <long long>(n);
        }
};

void parseInput(vector <string> &input, MonkeyData &monkeyData, long long &MODULO) {
    for (int i = 0; i < input.size(); i += 7) {
        int monkey = i / 7;
        stringstream line;
        string s;
        int number;
        line << input[i + 1];
        line >> s >> s;
        while (line >> number) {
            monkeyData.startItems[monkey].push_back(number);
            if (line.rdbuf()->in_avail() != 0)
                line >> s;
        }
        line = stringstream();
        line << input[i + 2];
        line >> s >> s >> s >> s;
        line >> monkeyData.op[monkey];
        line >> s;
        if (s == "old") {
            monkeyData.op[monkey] = '^';
            monkeyData.op2[monkey] = 1;
        }
        else {
            monkeyData.op2[monkey] = stoi(s);
        }
        line = stringstream();
        line << input[i + 3];
        line >> s >> s >> s >> monkeyData.test[monkey];
        line = stringstream();
        line << input[i + 4];
        line >> s >> s >> s >> s >> s >> monkeyData.monkeyA[monkey];
        line = stringstream();
        line << input[i + 5];
        line >> s >> s >> s >> s >> s >> monkeyData.monkeyB[monkey];
        MODULO *= monkeyData.test[monkey];
    }
}

long long simulateRounds(int monkeys, MonkeyData &monkeyData, long long MODULO, int roundCount, bool moduloActive) {
    deque <long long> items[monkeys];
    long long inspectCount[monkeys];
    for (int i = 0; i < monkeys; i++) {
        inspectCount[i] = 0;
        items[i] = monkeyData.startItems[i];
    }

    for (int round = 0; round < roundCount; round++) {
        for (int i = 0; i < monkeys; i++) {
            inspectCount[i] += items[i].size();
            while (items[i].size() > 0) {
                long long value = items[i].front();
                long long newValue = value;
                char op2 = monkeyData.op2[i];
                items[i].pop_front();

                switch (monkeyData.op[i]) {
                    case '+':
                        newValue += op2;
                        break;
                    case '-':
                        newValue -= op2;
                        break;
                    case '*':
                        newValue *= op2;
                        break;
                    case '/':
                        newValue /= op2;
                        break;
                    case '^':
                        newValue *= value;
                        break;
                }

                if (moduloActive) {
                    newValue %= MODULO;
                }
                else {
                    newValue /= 3;
                }

                if (newValue % monkeyData.test[i] == 0) {
                    items[monkeyData.monkeyA[i]].push_back(newValue);
                }
                else {
                    items[monkeyData.monkeyB[i]].push_back(newValue);
                }
            }
        }
    }
    vector <long long> inspects;
    for (int i = 0; i < monkeys; i++) {
        inspects.push_back(inspectCount[i]);
    }
    sort(inspects.rbegin(), inspects.rend());
    return inspects[0] * inspects[1];
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    int monkeys = input.size() / 7;
    long long MODULO = 1;
    MonkeyData monkeyData = MonkeyData(monkeys);
    
    parseInput(input, monkeyData, MODULO);
    std::cout << "Part 1: " << simulateRounds(monkeys, monkeyData, MODULO, 20, 0) << endl;
    std::cout << "Part 2: " << simulateRounds(monkeys, monkeyData, MODULO, 10000, 1) << endl;
    return 0;
}
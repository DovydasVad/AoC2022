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

const long long NO_VALUE = -2000000000000000;

class Monkey {
    public:
        string name;
        long long value;
        Monkey* monkeyA;
        char op;
        Monkey* monkeyB;

        Monkey(string name_) {
            name = name_;
            value = NO_VALUE;
            monkeyA = nullptr;
            monkeyB = nullptr;
        }

        void setOperation(Monkey* monkeyA_, char op_, Monkey* monkeyB_) {
            monkeyA = monkeyA_;
            op = op_;
            monkeyB = monkeyB_;
        }

        void setValue(long long value_) {
            value = value_;
        }

        void clearValue() {
            if (monkeyA != nullptr) {
                value = NO_VALUE;
            }
        }
};

Monkey* getMonkey(string name, map <string, Monkey*> &monkeyMap) {
    if (monkeyMap.find(name) == monkeyMap.end()) {
        Monkey* monkey = new Monkey(name);
        monkeyMap.emplace(name, monkey);
    }
    return monkeyMap.at(name);
}

void buildMonkeyMap(vector <string> input, map <string, Monkey*> &monkeyMap) {
    for (int i = 0; i < input.size(); i++) {
        string monkeyName, monkeyA, monkeyB, s;
        char op;
        stringstream ss;
        ss << input[i];
        ss >> monkeyName >> s;
        monkeyName = monkeyName.substr(0, 4);
        Monkey *monkey = getMonkey(monkeyName, monkeyMap);
        if (ss.rdbuf()->in_avail() != 0) {
            ss >> op >> monkeyB;
            monkeyA = s;
            monkey->setOperation(getMonkey(monkeyA, monkeyMap), op, getMonkey(monkeyB, monkeyMap));
        }
        else {
            monkey->value = stoll(s);
        }
    }
}

int validDivision;
long long getResult(Monkey* monkey) {
    if (monkey->value == NO_VALUE) {
        switch (monkey->op) {
            case '+':
                monkey->value = getResult(monkey->monkeyA) + getResult(monkey->monkeyB);
                break;
            case '-':
                monkey->value = getResult(monkey->monkeyA) - getResult(monkey->monkeyB);
                break;
            case '*':
                monkey->value = getResult(monkey->monkeyA) * getResult(monkey->monkeyB);
                break;
            case '/':
                monkey->value = getResult(monkey->monkeyA) / getResult(monkey->monkeyB);
                if (getResult(monkey->monkeyA) % getResult(monkey->monkeyB) != 0) {
                    validDivision = 0;
                }
                break;
            case '=':
                long long resultA, resultB;
                resultA = getResult(monkey->monkeyA);
                resultB = getResult(monkey->monkeyB);
                if (resultA > resultB) {
                    monkey->value = 1;
                }
                else if (resultA < resultB) {
                    monkey->value = -1;
                }
                else {
                    monkey->value = 0;
                }
                break;
        }
    }
    return monkey->value;
}

long long part1(map <string, Monkey*> &monkeyMap) {
    return getResult(getMonkey("root", monkeyMap));
}

long long part2(map <string, Monkey*> &monkeyMap) {
    getMonkey("root", monkeyMap)->op = '=';
    long long valueL = -2000000000000000, valueR = 2000000000000000, value;
    while (valueR - valueL > 1) {
        for (map <string, Monkey*> :: iterator it = monkeyMap.begin(); it != monkeyMap.end(); it++) {
            it->second->clearValue();
        }
        value = (valueL + valueR) / 2;
        getMonkey("humn", monkeyMap)->value = value;
        validDivision = 1;
        long long result = getResult(getMonkey("root", monkeyMap));
        if (result == 1) {
            valueL = value;
        }
        else if (result == -1 || (result == 0 && validDivision == 0)) {
            valueR = value;
        }
        else {
            return value;
        }
    }
    return -1;
}

void solve(vector <string> input) {
    map <string, Monkey*> monkeyMap;
    buildMonkeyMap(input, monkeyMap);
    cout << "Part 1: " << part1(monkeyMap) << endl;
    cout << "Part 2: " << part2(monkeyMap) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
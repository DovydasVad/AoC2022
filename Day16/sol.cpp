#include <bits/stdc++.h>

using namespace std;

vector <string> readInput() {
    vector <string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    return input;
}

class State {
    public:
        int rate;
        int sum;
        int activeValves = 0;
        bitset <100> active;
};

void parseInput(vector <string> &input, int &valveCount, int &openableValves, int rates[], map <string, int> &nameToId, vector <int> adjList[]) {
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input[i];
        string s, valve, valve2;
        char c, c2, comma;
        int rate;
        ss >> s >> valve >> s >> s >> c >> c >> c >> c >> c >> rate >> c >> s >> s >> s >> s;
        if (nameToId.find(valve) == nameToId.end()) {
            valveCount++;
            nameToId[valve] = valveCount;
        }
        if (rate > 0) {
            openableValves++;
        }
        int valveA, valveB;
        valveA = nameToId[valve];
        rates[valveA] = rate;
        while (ss >> c) {
            valve2 = c;
            ss >> c2;
            valve2 += c2;
            if (nameToId.find(valve2) == nameToId.end()) {
                valveCount++;
                nameToId[valve2] = valveCount;
            }
            valveB = nameToId[valve2];
            adjList[valveA].push_back(valveB);
            if (ss.rdbuf()->in_avail() != 0)
                ss >> comma;
        }
    }
}

void checkForBetterStates(vector <State> &existingStates, State state) {
    bool betterExists = false;
    for (int o = 0; o < existingStates.size(); o++) {
        State existingState = existingStates[o];
        if (existingState.active == state.active) {
            if (state.rate <= existingState.rate && state.sum <= existingState.sum) {
                betterExists = true;
                break;
            }
            else if (state.rate >= existingState.rate && state.sum >= existingState.sum) {
                betterExists = true;
                existingStates[o].sum = state.sum;
                existingStates[o].rate = state.rate;
                break;
            }
        }
    }
    if (betterExists == false) {
        existingStates.push_back(state);
    }
}

void simulateProcess(int allowedTime, int valveCount, int openableValves, int rates[], map <string, int> &nameToId, vector <int> adjList[], vector <State> currentStates[]) {
    State initial;
    bitset <100> initialBitset;
    vector <State> previousStates[valveCount + 1];

    initial.rate = 0;
    initial.sum = 0;
    initial.active = initialBitset;
    currentStates[nameToId["AA"]].push_back(initial);

    for (int i = 0; i < allowedTime; i++) {
        for (int j = 1; j <= valveCount; j++) {
            previousStates[j] = currentStates[j];
        }
        for (int j = 1; j <= valveCount; j++) {
            for (int u = 0; u < previousStates[j].size(); u++) {
                State prevState = previousStates[j][u];
                for (int t = 0; t < adjList[j].size(); t++) {
                    int b = adjList[j][t];
                    State newState = prevState;
                    newState.sum += prevState.rate;
                    checkForBetterStates(currentStates[b], newState);
                }

                if (prevState.activeValves < openableValves) {
                    if (rates[j] > 0 && prevState.active[j] == 0) {
                        State newState = prevState;
                        newState.sum += prevState.rate;
                        newState.active[j] = 1;
                        newState.rate += rates[j];
                        newState.activeValves++;
                        checkForBetterStates(currentStates[j], newState);
                    }
                }
            }
        }
    }
}

long long part1(int valveCount, int openableValves, int rates[], map <string, int> &nameToId, vector <int> adjList[]) {
    vector <State> currentStates[100];
    simulateProcess(30, valveCount, openableValves, rates, nameToId, adjList, currentStates);
    int maxSum = 0;
    for (int j = 1; j <= valveCount; j++) {
        for (int u = 0; u < currentStates[j].size(); u++) {
            maxSum = max(maxSum, currentStates[j][u].sum);
        }
    }
    return maxSum;
}

long long part2(int valveCount, int openableValves, int rates[], map <string, int> &nameToId, vector <int> adjList[]) {
    vector <State> currentStates[100];
    simulateProcess(26, valveCount, openableValves, rates, nameToId, adjList, currentStates);
    int maxSum = 0;
    for (int i = 1; i <= valveCount; i++) {
        cout << "Progress: " << i << "/" << valveCount << endl;
        for (int j = i; j <= valveCount; j++) {
            for (int u = 0; u < currentStates[i].size(); u++) {
                for (int t = 0; t < currentStates[j].size(); t++) {
                    bitset <100> active1 = currentStates[i][u].active;
                    bitset <100> active2 = currentStates[j][t].active;
                    if (!(active1 & active2).any())
                        maxSum = max(maxSum, currentStates[i][u].sum + currentStates[j][t].sum);
                }
            }
        }
    }
    return maxSum;
}

void solve(vector <string> input) {
    map <string, int> nameToId;
    int valveCount = 0, openableValves = 0;
    int rates[input.size() + 1];
    vector <int> adjList[input.size() + 1];
    parseInput(input, valveCount, openableValves, rates, nameToId, adjList);
    cout << "Part 1: " << part1(valveCount, openableValves, rates, nameToId, adjList) << endl;
    cout << "Part 2: " << part2(valveCount, openableValves, rates, nameToId, adjList) << endl;
}
 
int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
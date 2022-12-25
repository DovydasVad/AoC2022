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

class Blueprint {
    public:
        int cost_ores[5];
        int cost_clay3;
        int cost_obsidian4;

        Blueprint() {};
        Blueprint(int o1, int o2, int o3, int o4, int c3, int ob4) {
            cost_ores[1] = o1;
            cost_ores[2] = o2;
            cost_ores[3] = o3;
            cost_ores[4] = o4;
            cost_clay3 = c3;
            cost_obsidian4 = ob4;
        }
};

Blueprint currentBlueprint;
int maxGeode = 0;

void Rec(int time, int timeMax, int robots[], int ores, int clay, int obsidian, int geodes, bool oConstruct, bool cConstruct) {
    if (robots[0] > min(2 * currentBlueprint.cost_ores[1], 4) || robots[1] > currentBlueprint.cost_clay3) {
        return;
    }
    if (time == timeMax) {
        maxGeode = max(maxGeode, geodes);
        return;
    }
    int constr3Possible = true, constrOPossible = true;
    if (robots[2] == 0 && ores >= currentBlueprint.cost_ores[1] && time <= 11) {
        ores -= currentBlueprint.cost_ores[1];
        robots[0]++;
        Rec(time + 1, timeMax, robots, ores + robots[0] - 1, clay + robots[1], obsidian + robots[2], geodes + robots[3], oConstruct, cConstruct);
        robots[0]--;
        ores += currentBlueprint.cost_ores[1];
    }
    else if (oConstruct == true) {
        constr3Possible = false;
    }
    if (ores < currentBlueprint.cost_ores[1]) {
        constrOPossible = false;
    }
    if (ores >= currentBlueprint.cost_ores[2] && time <= 20) {
        ores -= currentBlueprint.cost_ores[2];
        robots[1]++;
        Rec(time + 1, timeMax, robots, ores + robots[0], clay + robots[1] - 1, obsidian + robots[2], geodes + robots[3], false, cConstruct);
        robots[1]--;
        ores += currentBlueprint.cost_ores[2];
    }
    else if (cConstruct == true) {
        constr3Possible = false;
    }
    if (ores >= currentBlueprint.cost_ores[3] && clay >= currentBlueprint.cost_clay3 && (time <= 29 || true)) {
        ores -= currentBlueprint.cost_ores[3];
        clay -= currentBlueprint.cost_clay3;
        robots[2]++;
        Rec(time + 1, timeMax, robots, ores + robots[0], clay + robots[1], obsidian + robots[2] - 1, geodes + robots[3], oConstruct, false);
        robots[2]--;
        ores += currentBlueprint.cost_ores[3];
        clay += currentBlueprint.cost_clay3;
    }
    else {
        constr3Possible = false;
    }
    if (ores >= currentBlueprint.cost_ores[4] && obsidian >= currentBlueprint.cost_obsidian4) {
        ores -= currentBlueprint.cost_ores[4];
        obsidian -= currentBlueprint.cost_obsidian4;
        robots[3]++;
        Rec(time + 1, timeMax, robots, ores + robots[0], clay + robots[1], obsidian + robots[2], geodes + robots[3] - 1, oConstruct, cConstruct);
        robots[3]--;
        ores += currentBlueprint.cost_ores[4];
        obsidian += currentBlueprint.cost_obsidian4;
    }
    if (ores >= currentBlueprint.cost_ores[4] && obsidian >= currentBlueprint.cost_obsidian4) {
        if (constr3Possible == false) {
            Rec(time + 1, timeMax, robots, ores + robots[0], clay + robots[1], obsidian + robots[2], geodes + robots[3], oConstruct, cConstruct);
        }
    }
    else if (oConstruct == false || constrOPossible == false) {
        Rec(time + 1, timeMax, robots, ores + robots[0], clay + robots[1], obsidian + robots[2], geodes + robots[3], oConstruct, cConstruct);
    }
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    int qualitySum = 0;
    Blueprint blueprints[input.size()];

    int o1, o2, o3, o4, c3, ob4;
    for (int i = 0; i < input.size(); i++) {
        string s;
        stringstream ss;
        ss << input[i];
        ss >> s >> s >> s >> s >> s >> s >> o1 >> s >> s >> s >> s >> s >> o2 >> s >> s >> s >> s >> s >> o3 >> s >> s >> c3 >> s >> s >> s >> s >> s >> o4 >> s >> s >> ob4 >> s;
        blueprints[i] = Blueprint(o1, o2, o3, o4, c3, ob4);
    }

    for (int i = 0; i < 30; i++) {
        currentBlueprint = blueprints[i];
        int robots[4] = {1, 0, 0, 0};
        maxGeode = 0;
        Rec(0, 24, robots, 0, 0, 0, 0, true, true);
        qualitySum += (i + 1) * maxGeode;
    }
    cout << "Part 1: " << qualitySum << endl;

    int qualityMult = 1;
    for (int i = 0; i < 3; i++) {
        currentBlueprint = blueprints[i];
        int robots[4] = {1, 0, 0, 0};
        maxGeode = 0;
        Rec(0, 32, robots, 0, 0, 0, 0, true, true);
        qualityMult *= maxGeode;
    }
    cout << "Part 2: " << qualityMult << endl;
    return 0;
}
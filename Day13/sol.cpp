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

class List {
    public:
        vector <List> values = {};
        int intValue = -1;
};

List getList(string s) {
    int number = -1;
    stack <vector<List>> listLevels;
    listLevels.push(vector<List>());
    for (int i = 0; i < s.length(); i++) {
        char c = s.at(i);
        if (c >= '0' && c <= '9') {
            if (number == -1) {
                number = c - '0';
            }
            else {
                number *= 10;
                number += c - '0';
            }
        }
        else if (c == '[') {
            listLevels.push(vector<List>());
        }
        else if (c == ',') {
            if (number != -1) {
                List ls;
                ls.intValue = number;
                listLevels.top().push_back(ls);
            }
            number = -1;
        }
        else if (c == ']') {
            if (number != -1) {
                List ls;
                ls.intValue = number;
                listLevels.top().push_back(ls);
            }
            List curr;
            curr.values = listLevels.top();
            listLevels.pop();
            listLevels.top().push_back(curr);
            number = -1;
        }
    }
    List res;
    res.values = listLevels.top();
    return res;
}

int isRightOrder(List LA, List LB) {
    if (LA.intValue != -1 && LB.intValue != -1) {
        if (LA.intValue < LB.intValue) {
            return 1;
        }
        else if (LA.intValue == LB.intValue) {
            return 0;
        }
        else {
            return -1;
        }
    }
    else if (LA.intValue == -1 && LB.intValue == -1) {
        for (int i = 0; i < LA.values.size(); i++) {
            if (i >= LB.values.size()) {
                return -1;
            }
            int comparison = isRightOrder(LA.values[i], LB.values[i]);
            if (comparison != 0) {
                return comparison;
            }
        }
        if (LA.values.size() < LB.values.size()) {
            return 1;
        }
        return 0;
    }
    else if (LA.intValue != -1) {
        List left;
        left.values = {LA};
        return isRightOrder(left, LB);
    }
    else if (LB.intValue != -1) {
        List right;
        right.values = {LB};
        return isRightOrder(LA, right);
    }
    return 0;
}

long long part1(vector <string> &input) {
    long long sum = 0;
    for (int i = 0; i < input.size(); i += 3) {
        stringstream ss;
        string s = input.at(i);
        List LA, LB;
        LA = getList(input.at(i));
        LB = getList(input.at(i + 1));
        if (isRightOrder(LA, LB) == 1) {
            sum += i / 3 + 1;
        }
    }
    return sum;
}

long long part2(vector <string> &input) {
    vector <pair<List, int>> lists;
    for (int i = 0; i < input.size(); i += 3) {
        List LA, LB;
        LA = getList(input.at(i));
        LB = getList(input.at(i + 1));
        lists.push_back({LA, 0});
        lists.push_back({LB, 0});
    }
    
    lists.push_back({getList("[[2]]"), 1});
    lists.push_back({getList("[[6]]"), 2});

    sort(lists.begin(), lists.end(), [](const pair<List, int>& lhs, const pair<List, int>& rhs) {
        return max(isRightOrder(lhs.first, rhs.first), 0);
    });

    int positions[3];
    for (int i = 0; i < lists.size(); i++) {
        positions[lists.at(i).second] = i + 1;
    }
    return positions[1] * positions[2];
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
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

void preprocess(vector <string> &input, map <string, int> &size, set <string> &allDirs) {
    input.push_back("$ cd /");
    vector <string> currentPath;
    string currString = "";
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input.at(i);
        string s;
        ss >> s;
        if (s == "$") {
            ss >> s;
            if (s == "ls") {
                continue;
            }
            ss >> s;
            if (s == "/") {
                while (currentPath.size() > 0) {
                    currentPath.pop_back();
                }
                currentPath.push_back("/");
                if (allDirs.find("/") == allDirs.end()) {
                    allDirs.insert("/");
                }
                currString = "/";
            }
            else {
                if (s == "..") {
                    currentPath.pop_back();
                    currString = currentPath.back();
                }
                else {
                    currString += s + "/";
                    currentPath.push_back(currString);
                    if (allDirs.find(currString) == allDirs.end()) {
                        allDirs.insert(currString);
                    }
                }
            }
        }
        else {
            for (int j = i; j < input.size(); j++) {
                stringstream ss2;
                ss2 << input.at(j);
                string s, name;
                ss2 >> s >> name;
                if (s == "dir") {
                    string newCurrString = currString + name + "/";
                    if (allDirs.find(newCurrString) == allDirs.end()) {
                        allDirs.insert(newCurrString);
                    }
                }
                else if (s != "$") {
                    string dir = currentPath.back();
                    int dirSize = stoi(s);
                    for (int u = 0; u < currentPath.size(); u++) {
                        string dirIn = currentPath[u];
                        size[dirIn] += dirSize;
                    }
                }
                else {
                    i = j - 1;
                    break;
                }
            }
        }
    }
}

long long part1(map <string, int> &size, set <string> &allDirs) {
    long long sum = 0;
    for (set <string> :: iterator it = allDirs.begin(); it != allDirs.end(); it++) {
        string dir = *it;
        if (size[dir] <= 100000) {
            sum += size[dir];
        }
    }
    return sum;
}

long long part2(map <string, int> &size, set <string> &allDirs) {
    long long total = size["/"], bestSize = 999999999;
    for (set <string> :: iterator it = allDirs.begin(); it != allDirs.end(); it++) {
        string dir = *it;
        if (total - size[dir] <= 40000000) {
            if (size[dir] < bestSize) {
                bestSize = size[dir];
            }
        }
    }
    return bestSize;
}

void solve(vector <string> input) {
    map <string, int> size;
    set <string> allDirs;
    preprocess(input, size, allDirs);
    cout << "Part 1: " << part1(size, allDirs) << endl;
    cout << "Part 2: " << part2(size, allDirs) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
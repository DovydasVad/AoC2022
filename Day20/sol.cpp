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

class FileNumber {
    public:
        long long originalValue;
        long long value;
        long long id;

        FileNumber(long long originalvalue_, long long value_, long long id_) {
            originalValue = originalvalue_;
            value = value_;
            id = id_;
        }
};

vector <FileNumber> getInitList(vector <string> &input) {
    int n = input.size();
    vector <FileNumber> initList;
    for (int i = 0; i < n; i++) {
        int a = stoi(input[i]);
        FileNumber fileNumber = a != 0 ? FileNumber(a, a % (n - 1), i) : FileNumber(0, 0, -1);
        initList.push_back(fileNumber);
    }
    return initList;
}

int findNumberPosition(vector <FileNumber> list, long long ID) {
    for (int i = 0; i < list.size(); i++) {
        if (list.at(i).id == ID) {
            return i;
        }
    }
    return -1;
}

void initiateList(vector <FileNumber> &list, vector <FileNumber> &initList, long long decryptionKey) {
    list.clear();
    for (int i = 0; i < initList.size(); i++) {
        FileNumber fileNumber = initList.at(i);
        fileNumber.originalValue *= decryptionKey;
        long long sign = 1;
        if (fileNumber.originalValue < 0) {
            sign = -1;
        }
        fileNumber.value = ((fileNumber.originalValue * sign) % (initList.size() - 1)) * sign;
        list.push_back(fileNumber);
    }
}

void mixList(vector <FileNumber> &list, vector <FileNumber> &initList, int times) {
    int n = list.size();
    for (int t = 0; t < times; t++) {
        for (int i = 0; i < n; i++) {
            FileNumber number = initList.at(i);
            int index = findNumberPosition(list, number.id);
            number = list.at(index);
            if (number.value == 0) {
                continue;
            }
            long long sign = number.value / abs(number.value);
            long long mixes = number.value * sign;
            while (mixes > 0) {
                int nextIndex = (index + n + sign) % n;
                swap(list.at(index), list.at(nextIndex));
                index = nextIndex;
                mixes--;
            }
        }
    }
}

long long getGrooveCoordinates(vector <FileNumber> &list) {
    int index = findNumberPosition(list, -1);  // finding number 0
    long long groove = 0;
    int n = list.size();
    for (int i = 1; i <= 3000; i++) {
        index++;
        index %= n;
        if (i % 1000 == 0) {
            groove += list.at(index).originalValue;
        }
    }
    return groove;
}

long long part1(vector <string> &input, vector <FileNumber> initList) {
    vector <FileNumber> list;
    initiateList(list, initList, 1);
    mixList(list, initList, 1);
    return getGrooveCoordinates(list);
}

long long part2(vector <string> &input, vector <FileNumber> initList) {
    vector <FileNumber> list;
    initiateList(list, initList, 811589153);
    mixList(list, initList, 10);
    return getGrooveCoordinates(list);
}

void solve(vector <string> input) {
    vector <FileNumber> initList = getInitList(input);
    cout << "Part 1: " << part1(input, initList) << endl;
    cout << "Part 2: " << part2(input, initList) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}
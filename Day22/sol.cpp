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

class Coordinate {
    public:
        int y;
        int x;

        Coordinate(int y_, int x_) {
            y = y_;
            x = x_;
        }

        Coordinate(int directionValue) {
            x = 0;
            y = 0;
            directionValue = (directionValue + 4) % 4;
            switch (directionValue) {
                case 0:
                    x = 1;
                    break;
                case 1:
                    y = 1;
                    break;
                case 2:
                    x = -1;
                    break;
                case 3:
                    y = -1;
                    break;
            }
        }

        Coordinate operator + (Coordinate &coord) {
            return Coordinate(y + coord.y, x + coord.x);
        }

        Coordinate operator - (Coordinate &coord) {
            return Coordinate(y - coord.y, x - coord.x);
        }
};

int getDirectionValue(Coordinate direction) {
    if (direction.y == 0 && direction.x == 1) {
        return 0;
    }
    else if (direction.y == 1 && direction.x == 0) {
        return 1;
    }
    else if (direction.y == 0 && direction.x == -1) {
        return 2;
    }
    else {
        return 3;
    }
}

void makeField(vector <string> &input, vector <string> &field, string &path) {
    field.push_back("");
    int maxLength = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input.at(i).size() == 0 || input.at(i).at(0) < '0' || input.at(i).at(0) > '9') {
            field.push_back(" " + input.at(i) + " ");
            maxLength = max(maxLength, (int)field.at(i).length());
        }
        else {
            path = input.at(i);
        }
    }
    for (int i = 0; i < field.size(); i++) {
        while (field.at(i).length() < maxLength) {
            field.at(i).push_back(' ');
        }
    }
}

Coordinate getStartingPosition(vector <string> &field) {
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field.at(i).length(); j++) {
            if (field.at(i).at(j) == '.') {
                return Coordinate(i, j);
            }
        }
    }
    return Coordinate(-1, -1);
}

Coordinate makeTurn(Coordinate direction, char turn) {
    if (turn == 'L') {
        return Coordinate(getDirectionValue(direction) - 1);
    }
    else {
        return Coordinate(getDirectionValue(direction) + 1);
    }
}

void getWrapPosition(Coordinate &position, Coordinate &direction, vector <string> &field, bool inCube) {
    if (inCube == false) {
        if (direction.y == -1) {
            position.y = field.size() - 1;
        }
        else if (direction.y == 1) {
            position.y = 0;
        }
        else if (direction.x == -1) {
            position.x = field.at(0).length() - 1;
        }
        else if (direction.x == 1) {
            position.x = 0;
        }
    }
    else { // Direction rules are based on the input cube
        position = position - direction;
        if (direction.y == -1) {
            if (position.x <= 50) {
                position = Coordinate(50 + position.x, 50);
                direction = Coordinate(0, 1);
            }
            else if (position.x <= 100) {
                position = Coordinate(150 + (position.x - 50), 0);
                direction = Coordinate(0, 1);
            }
            else if (position.x <= 150) {
                position = Coordinate(200, 0 + (position.x - 100));
                direction = Coordinate(-1, 0);
            }
        }
        else if (direction.y == 1) {
            if (position.x <= 50) {
                position = Coordinate(0, 100 + position.x);
                direction = Coordinate(1, 0);
            }
            else if (position.x <= 100) {
                position = Coordinate(150 + (position.x - 50), 50);
                direction = Coordinate(0, -1);
            }
            else if (position.x <= 150) {
                position = Coordinate(50 + (position.x - 100), 100);
                direction = Coordinate(0, -1);
            }
        }
        else if (direction.x == -1) {
            if (position.y <= 50) {
                position = Coordinate(151 - position.y, 0);
                direction = Coordinate(0, 1);
            }
            else if (position.y <= 100) {
                position = Coordinate(100, position.y - 50);
                direction = Coordinate(1, 0);
            }
            else if (position.y <= 150) {
                position = Coordinate(151 - position.y, 50);
                direction = Coordinate(0, 1);
            }
            else if (position.y <= 200) {
                position = Coordinate(0, 50 + position.y - 150);
                direction = Coordinate(1, 0);
            }
        }
        else if (direction.x == 1) {
            if (position.y <= 50) {
                position = Coordinate(100 + 51 - position.y, 100);
                direction = Coordinate(0, -1);
            }
            else if (position.y <= 100) {
                position = Coordinate(50, 100 + (position.y - 50));
                direction = Coordinate(-1, 0);
            }
            else if (position.y <= 150) {
                position = Coordinate(51 - (position.y - 100), 150);
                direction = Coordinate(0, -1);
            }
            else if (position.y <= 200) {
                position = Coordinate(150, 50 + (position.y - 150));
                direction = Coordinate(-1, 0);
            }
        }
    }
    while (field.at(position.y).at(position.x) == ' ') {
        position = position + direction;
    }
}

void makeMove(Coordinate &position, int tilesToMove, Coordinate &direction, vector <string> &field, bool inCube) {
    while (tilesToMove > 0) {
        Coordinate newPosition = position + direction;
        Coordinate prevDirection = direction;
        if (field.at(newPosition.y).at(newPosition.x) == ' ') {
            getWrapPosition(newPosition, direction, field, inCube);
        }
        if (field.at(newPosition.y).at(newPosition.x) == '.') {
            position = newPosition;
        }
        else {
            direction = prevDirection;
            break;
        }
        tilesToMove--;
    }
}

long long traverseField(vector <string> &field, string &path, bool inCube) {
    Coordinate position = getStartingPosition(field), direction = Coordinate(0, 1);
    stringstream ssPath;
    ssPath << path;
    bool readNumber = true;
    int tilesToMove;
    char turn;
    while (ssPath.rdbuf()->in_avail() != 0) {
        if (readNumber) {
            ssPath >> tilesToMove;
            makeMove(position, tilesToMove, direction, field, inCube);
        }
        else {
            ssPath >> turn;
            direction = makeTurn(direction, turn);
        }
        readNumber = !readNumber;
    }
    return 1000 * position.y + 4 * position.x + getDirectionValue(direction);
}

long long part1(vector <string> &field, string &path) {
    return traverseField(field, path, false);
}

long long part2(vector <string> &field, string &path) {
    return traverseField(field, path, true);
}

void solve(vector <string> input) {
    vector <string> field;
    string path;
    makeField(input, field, path);
    cout << "Part 1: " << part1(field, path) << endl;
    cout << "Part 2: " << part2(field, path) << endl;
}

int main() {
    freopen("input.in", "r", stdin);
    solve(readInput());
    return 0;
}

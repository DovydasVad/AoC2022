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

int getSurfaceArea(vector <int> &X, vector <int> &Y, vector <int> &Z) {
    int n = X.size();
    int surfaceArea = 0;
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < 6; s++) {
            bool isFaceConnected = false;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int diff = abs(X[i] - X[j]) + abs(Y[i] - Y[j]) + abs(Z[i] - Z[j]);
                if (diff != 1) {
                    continue;
                }
                if (s == 0 && X[i] - X[j] == -1) {
                    isFaceConnected = true;
                }
                if (s == 1 && X[i] - X[j] == 1) {
                    isFaceConnected = true;
                }
                if (s == 2 && Y[i] - Y[j] == -1) {
                    isFaceConnected = true;
                }
                if (s == 3 && Y[i] - Y[j] == 1) {
                    isFaceConnected = true;
                }
                if (s == 4 && Z[i] - Z[j] == -1) {
                    isFaceConnected = true;
                }
                if (s == 5 && Z[i] - Z[j] == 1) {
                    isFaceConnected = true;
                }
            }
            if (isFaceConnected == false) {
                surfaceArea++;
            }
        }
    }
    return surfaceArea;
}

int main() {
    freopen("input.in", "r", stdin);
    vector <string> input = readInput();
    vector <int> X, Y, Z;
    int x, y, z;
    char comma;
    for (int i = 0; i < input.size(); i++) {
        stringstream ss;
        ss << input[i];
        ss >> x >> comma >> y >> comma >> z;
        X.push_back(x);
        Y.push_back(y);
        Z.push_back(z);
    }
    int surfaceArea = getSurfaceArea(X, Y, Z);
    cout << "Part 1: " << surfaceArea << endl;

    int n = X.size();
    int visited[21][21][21];
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j <= 20; j++) {
            for (int u = 0; u <= 20; u++) {
                visited[i][j][u] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        visited[X[i]][Y[i]][Z[i]] = 1;
    }
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j <= 20; j++) {
            for (int u = 0; u <= 20; u++) {
                if (visited[i][j][u] == 0) {
                    vector <pair <pair<int, int>, int>> T;
                    T.push_back({{i, j}, u});
                    visited[i][j][u] = 1;
                    bool insideLava = true;
                    vector <int> X1, Y1, Z1;
                    for (int o = 0; o < T.size(); o++) {
                        int x, y, z;
                        x = T[o].first.first;
                        y = T[o].first.second;
                        z = T[o].second;
                        X1.push_back(x);
                        Y1.push_back(y);
                        Z1.push_back(z);
                        if (x == 0 || x == 20 || y == 0 || y == 20 || z == 0 || z == 20) {
                            insideLava = false;
                        }
                        if (x - 1 >= 0 && visited[x - 1][y][z] == 0) {
                            visited[x - 1][y][z] = 1;
                            T.push_back({{x - 1, y}, z});
                        }
                        if (x + 1 <= 20 && visited[x + 1][y][z] == 0) {
                            visited[x + 1][y][z] = 1;
                            T.push_back({{x + 1, y}, z});
                        }
                        if (y - 1 >= 0 && visited[x][y - 1][z] == 0) {
                            visited[x][y - 1][z] = 1;
                            T.push_back({{x, y - 1}, z});
                        }
                        if (y + 1 <= 20 && visited[x][y + 1][z] == 0) {
                            visited[x][y + 1][z] = 1;
                            T.push_back({{x, y + 1}, z});
                        }
                        if (z - 1 >= 0 && visited[x][y][z - 1] == 0) {
                            visited[x][y][z - 1] = 1;
                            T.push_back({{x, y}, z - 1});
                        }
                        if (z + 1 <= 20 && visited[x][y][z + 1] == 0) {
                            visited[x][y][z + 1] = 1;
                            T.push_back({{x, y}, z + 1});
                        }
                    }
                    if (insideLava == true) {
                        surfaceArea -= getSurfaceArea(X1, Y1, Z1);
                        for (int o = 0; o < X1.size(); o++) {
                            int x, y, z;
                            x = X1[o];
                            y = Y1[o];
                            z = Z1[o];
                            if (x == 0 || x == 20 || y == 0 || y == 20 || z == 0 || z == 20) {
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "Part 2: " << surfaceArea << endl;
    return 0;
}

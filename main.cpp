#include "labs.h"
#include "vector"
#include "algorithm"

using namespace std;

void elena_task2() {
    int n, target, multiplicity = 0, minimal = 0, maximal = 0, foundMaximals = 0, oddSum = 0;
    cin >> n >> target;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] % target == 0)
            multiplicity += a[i];
        if (a[i] <= a[minimal])
            minimal = i;
        if (a[i] > a[maximal]) {
            maximal = i;
            foundMaximals = 1;
        } else if (a[i] == a[maximal] && foundMaximals < 2) {
            maximal = i;
            ++foundMaximals;
        }
    }
    const int left = minimal < maximal ? minimal + 1 : maximal + 1, right = maximal > minimal ? maximal : minimal;
    for (int i = left; i < right; ++i)
        if (a[i] % 2 != 0)
            oddSum += a[i];

    cout << multiplicity << " " << oddSum << endl;

    int converted[n - 1 - foundMaximals];
    bool isMinimalDeleted = false;
    for (int i = 0, j = 0; i < n; ++i) {
        if (!isMinimalDeleted && a[i] == a[minimal]) {
            isMinimalDeleted = true;
            continue;
        }
        if (a[i] == a[maximal])
            continue;
        converted[j] = a[i];
        ++j;
    }
    for (int i = 0; i < n - 1 - foundMaximals; ++i) {
        cout << converted[i] << " ";
    }
}

void elena_task1() {
    int n, m;
    cin >> n >> m;
    int diagonalModifier = min(n, m);
    int a[n][m];
    vector<int> xs = {};
    vector<int> ys = {};
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cin >> a[x][y];
            if (x < y && x + y < diagonalModifier - 1) {
                int test = a[x][y];
                if (a[x][y] == 0) {
                    xs.push_back(x);
                    ys.push_back(y);
                }
            }
        }
    }

    vector<vector<int>> converted = {};
    for (int x = 0; x < n; ++x) {
        if (find(xs.begin(), xs.end(), x) == xs.end()) {
            vector<int> line = {};
            for (int y = 0; y < m; ++y)
                if (find(ys.begin(), ys.end(), y) == ys.end())
                    line.push_back(a[x][y]);
            converted.push_back(line);
        }
    }

    for (auto &i: converted) {
        for (int j: i) {
            cout << j << " ";
        }
        cout << endl;
    }
}


int main() {
    system("chcp 65001");
    std::cout << std::fixed;
    freopen("C:\\Users\\Ivan\\CLionProjects\\ETU\\input.txt", "r", stdin);
    freopen("C:\\Users\\Ivan\\CLionProjects\\ETU\\output.txt", "w+", stdout);
    return lab3();
}
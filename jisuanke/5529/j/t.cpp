#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int n;
int e[N][N];

void fix(int x, int y) {
    e[x][y] = e[y][x] = 1;
}

int find(int x) {
    for (int i = 1; i <= n; ++i) {
        if (!e[x][i])
            return i;
    }
    return -1;
}

int main() {
    while (cin >> n) {
        memset(e, 0, sizeof e);
        vector<int> vec;
        for (int i = 1; i <= n; ++i) e[i][i] = 1;
        for (int cas = n - 1; cas >= 1; --cas) {
            vec.clear();
            vec.push_back(n);
            while (vec.size() <= cas) {
                int nxt = find(vec.end()[-1]);
                if (nxt == -1) {
                    cout << "BUG" << endl;
                    return 0;
                }
                fix(nxt, vec.end()[-1]);
                vec.push_back(nxt);
            }
            for (auto it : vec) {
                cout << it << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

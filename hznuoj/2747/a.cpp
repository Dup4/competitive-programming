#include <bits/stdc++.h>
using namespace std;

string get(int x) {
    string s = "";
    while (x) {
        s += x % 10 + '0';
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int n, m;
    cin >> n >> m;
    int x[2], y[2], p;
    vector<vector<string>> G(n, vector<string>(m, "."));
    while (cin >> x[0] >> y[0]) {
        if (x[0] + y[0] == 0)
            break;
        cin >> x[1] >> y[1] >> p;
        for (int i = 0; i < 2; ++i) G[x[i] - 1][y[i] - 1] = get(p);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cout << G[i][j] << " \n"[j == m - 1];
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, R, C;
int p[200000], f[200000];
int find(int u) {
    if (p[u] == u)
        return u;
    return p[u] = find(p[u]);
}
int main() {
    scanf("%d%d%d", &n, &R, &C);
    vector<vector<int> > v(n, vector<int>(3));
    for (auto &x : v) {
        for (auto &y : x) scanf("%d", &y);
        swap(x[0], x[2]);
        swap(x[1], x[2]);
    }
    sort(v.rbegin(), v.rend());
    ll res = 0;
    for (int i = 0; i < R + C; ++i) p[i] = i;
    for (auto &e : v) {
        int u = e[1] - 1;
        int v = e[2] - 1 + R;
        u = find(u);
        v = find(v);
        if (u != v && f[u] + f[v] < 2) {
            res += e[0];
            p[u] = v;
            f[v] |= f[u];
        } else if (u == v && !f[u]) {
            res += e[0];
            f[u] = true;
        }
    }
    cout << res << endl;
    return 0;
}

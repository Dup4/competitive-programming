#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, q;
vector<vector<int> > G;

struct node {
    int v, i;

    node() {}

    node(int v, int i) : v(v), i(i) {}

    bool operator<(const node &other) const {
        return v < other.v;
    }
} a[N], b[N];

bool gao() {
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i];
    }
    for (int cas = 1; cas <= m; ++cas) {
        sort(b + 1, b + 1 + n);
        int r = G[cas].size();
        for (int i = 1; i <= r; ++i) {
            if (b[i].i == 1)
                return false;
            b[i] = node(G[cas][i - 1], 0);
        }
    }
    return true;
}

int main() {
    cin >> n >> m >> q;
    G.clear();
    G.resize(m + 1);
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        a[i] = node(x, i == 1);
    }
    for (int i = 1, r, x; i <= m; ++i) {
        cin >> r;
        G[i].resize(r);
        for (auto &v : G[i]) cin >> v;
    }
    for (int i = 1, x, y, z; i <= q; ++i) {
        cin >> x >> y >> z;
        G[x][y - 1] = z;
        cout << gao() << endl;
    }
    return 0;
}

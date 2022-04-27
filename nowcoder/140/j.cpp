#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define pii pair<int, int>
#define fi first
#define se second
int n, m, q;
struct node {
    int x[2], y[2];
    node() {}
    node(int x1, int y1, int x2, int y2) {
        x[0] = x1;
        x[1] = x2;
        y[0] = y1;
        y[1] = y2;
    }
};
vector<vector<pii> > a;
vector<vector<node> > b;
vector<vector<int> > c;

struct BIT {
    vector<vector<int> > a;
    void init() {
        a.clear();
        a.resize(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            a[i].resize(m + 1);
        }
    }
    void update(int x, int y, int v) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                a[i][j] += v;
            }
        }
    }
    void update(int x1, int y1, int x2, int y2, int v) {
        update(x1, y1, v);
        update(x2 + 1, y2 + 1, v);
        update(x1, y2 + 1, -v);
        update(x2 + 1, y1, -v);
    }
    int query(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += a[i][j];
            }
        }
        return res;
    }
} bit;

void read(int &x) {
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()))
        ;
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        a.clear();
        a.resize(n * m + 1);
        b.clear();
        b.resize(n * m + 1);
        c.clear();
        c.resize(n + 10);
        for (int i = 0; i < n + 10; ++i) {
            c[i].resize(m + 10);
        }
        bit.init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1, x; j <= m; ++j) {
                read(x);
                a[x].emplace_back(i, j);
            }
        }
        for (int i = 1, k, x1, y1, x2, y2; i <= q; ++i) {
            read(x1);
            read(y1);
            read(x2);
            read(y2);
            read(k);
            b[k].push_back(node(x1, y1, x2, y2));
            ++c[x1][y1];
            ++c[x2 + 1][y2 + 1];
            --c[x2 + 1][y1];
            --c[x1][y2 + 1];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];
            }
        }
        int res = 0;
        for (int i = 1; i <= n * m; ++i) {
            for (auto it : b[i]) {
                bit.update(it.x[0], it.y[0], it.x[1], it.y[1], 1);
            }
            for (auto it : a[i]) {
                if (bit.query(it.fi, it.se) != c[it.fi][it.se]) {
                    ++res;
                }
            }
            for (auto it : b[i]) {
                bit.update(it.x[0], it.y[0], it.x[1], it.y[1], -1);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

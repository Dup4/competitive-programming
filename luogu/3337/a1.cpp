#include <bits/stdc++.h>
using namespace std;

template <class T>
struct LP {
    static const T INF = 0x3f3f3f3f;
    int n, m;
    vector<T> v;
    vector<vector<T> > a;
    LP(const vector<vector<T> > &_a, int _n, int _m) {
        a = _a;
        n = _n;
        m = _m;
        v.resize(m + 1);
    }
    void pivot(int x, int y) {
        int tp = 0;
        for (int i = 0; i <= m; i++)
            if (a[x][i])
                v[++tp] = i;
        for (int i = 0; i <= n; i++) {
            if (i != x && a[i][y]) {
                int k = a[i][y];
                a[i][y] = 0;
                for (int j = 1; j <= tp; j++) a[i][v[j]] -= k * a[x][v[j]];
            }
        }
    }
    T solve() {
        a[n + 1][0] = INF;
        while (1) {
            int x = 0, y = n + 1;
            for (int i = 1; i <= m; i++)
                if (a[0][i] > 0) {
                    x = i;
                    break;
                }
            if (!x)
                return -a[0][0];
            for (int i = 1; i <= n; i++)
                if (a[i][x] > 0 && a[i][0] < a[y][0])
                    y = i;
            pivot(y, x);
        }
    }
};

const int N = 1e4 + 10;
int n, m, a[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        vector<vector<int> > A(n + 2, vector<int>(m + 2, 0));
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), A[i][0] = a[i];
        for (int i = 1, l, r, d; i <= m; ++i) {
            scanf("%d%d%d", &l, &r, &d);
            A[0][i] = d;
            for (int j = l; j <= r; ++j) A[j][i] = 1;
        }
        LP<int> lp(A, n, m);
        printf("%d\n", lp.solve());
    }
    return 0;
}

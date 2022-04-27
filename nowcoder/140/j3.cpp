#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n, m, q;
vector<vector<int>> a, c;
vector<vector<ll>> b;
template <class T>
void up(vector<vector<T>> &vec, int x1, int y1, int x2, int y2, int v) {
    vec[x1][y1] += v;
    vec[x2 + 1][y2 + 1] += v;
    vec[x1][y2 + 1] -= v;
    vec[x2 + 1][y1] -= v;
}
template <class T>
void work(vector<vector<T>> &vec) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            vec[i][j] += vec[i - 1][j] + vec[i][j - 1] - vec[i - 1][j - 1];
        }
    }
}
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
        a.resize(n + 2, vector<int>(m + 2, 0));
        b.clear();
        b.resize(n + 2, vector<ll>(m + 2, 0));
        c.clear();
        c.resize(n + 2, vector<int>(m + 2, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                read(a[i][j]);
            }
        }
        int x[2], y[2], k;
        while (q--) {
            read(x[0]);
            read(y[0]);
            read(x[1]);
            read(y[1]);
            read(k);
            up(b, x[0], y[0], x[1], y[1], 1ll * k);
            up(c, x[0], y[0], x[1], y[1], 1);
        }
        work(b);
        work(c);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (b[i][j] != c[i][j] * a[i][j]) {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

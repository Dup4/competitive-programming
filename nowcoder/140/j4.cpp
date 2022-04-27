#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define y1 y_1
int x1[N], y1[N], x2[N], y2[N], k[N];
int n, m, q;
vector<vector<int>> a, b, c;
vector<vector<bool>> die;
void up(vector<vector<int>> &vec, int x1, int y1, int x2, int y2, int v) {
    vec[x1][y1] += v;
    vec[x2 + 1][y2 + 1] += v;
    vec[x1][y2 + 1] -= v;
    vec[x2 + 1][y1] -= v;
}
void work(vector<vector<int>> &vec) {
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
        b.resize(n + 2, vector<int>(m + 2, 0));
        die.clear();
        die.resize(n + 2, vector<bool>(m + 2, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i, k + i);
            up(b, x1[i], y1[i], x2[i], y2[i], 1);
        }
        work(b);
        for (int i = 15; i >= 0; --i) {
            c.clear();
            c.resize(n + 2, vector<int>(m + 2, 0));
            for (int j = 1; j <= q; ++j) {
                if (k[j] >> i & 1) {
                    up(c, x1[j], y1[j], x2[j], y2[j], 1);
                }
            }
            work(c);
            for (int _i = 1; _i <= n; ++_i) {
                for (int _j = 1; _j <= m; ++_j) {
                    if (a[_i][_j] >> i & 1) {
                        if (b[_i][_j] != c[_i][_j]) {
                            die[_i][_j] = 1;
                        }
                    } else if (c[_i][_j]) {
                        die[_i][_j] = 1;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                res += die[i][j];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

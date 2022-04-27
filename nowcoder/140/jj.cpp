#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 15500010
int prime[1000010], tot;
bool check[N];
void init() {
    tot = 0;
    memset(check, 0, sizeof check);
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++tot] = i;
            if (tot >= 1000000)
                break;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
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

int main() {
    init();
    cout << tot << endl;
    random_shuffle(prime + 1, prime + 1 + tot);
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        a.clear();
        a.resize(n + 2, vector<int>(m + 2, 0));
        b.clear();
        b.resize(n + 2, vector<ll>(m + 2, 0));
        c.clear();
        c.resize(n + 2, vector<int>(m + 2, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        int x[2], y[2], k;
        while (q--) {
            scanf("%d%d%d%d%d", x, y, x + 1, y + 1, &k);
            up(b, x[0], y[0], x[1], y[1], prime[k]);
            up(c, x[0], y[0], x[1], y[1], 1);
        }
        work(b);
        work(c);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (b[i][j] != c[i][j] * prime[a[i][j]]) {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

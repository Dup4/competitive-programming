#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int maxn = 1e2 + 10;
const int mod = 193;
int n, w[maxn];
ll m;
struct Matrix {
    int ans[maxn][maxn];
    Matrix() {
        memset(ans, 0, sizeof(ans));
    }
    inline void Init() {
        for (int i = 1; i <= n; ++i) ans[i][i] = 1;
    }
} res;
Matrix operator*(Matrix a, Matrix b) {
    Matrix tmp;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) tmp.ans[i][j] += a.ans[i][k] * b.ans[k][j];
            tmp.ans[i][j] %= mod;
        }
    }
    return tmp;
}
Matrix qmod(Matrix a, ll x) {
    Matrix tmp;
    tmp.Init();
    while (x) {
        if (x & 1)
            tmp = tmp * a;
        a = a * a;
        x >>= 1;
    }
    return tmp;
}

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for (int i = 1; i <= n - 1; ++i) res.ans[i][i + 1] = 1;
    for (int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        res.ans[i][1] = x;
    }
    res = qmod(res, m - n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = (ans + res.ans[i][1] * w[i]) % mod;
    printf("%d\n", ans);
    return 0;
}

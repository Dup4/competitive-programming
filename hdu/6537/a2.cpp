#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int blk, K, tot, n, m, pri[N], check[N], id1[N], id2[N], w[N], g[N], C[210][210];
inline int id(int x) {
    if (x <= blk)
        return id1[x];
    return id2[n / x];
}
inline void add(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
void sieve() {
    memset(check, 0, sizeof check);
    tot = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i])
            pri[++tot] = i;
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

int S(int x, int y, int K) {
    if (x <= 1 || pri[y] > x) {
        return 0;
    }
    int k = id(x);
    int res = 1ll * K * ((g[k] + mod - y + 1) % mod) % mod;
    for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
        ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
        for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
            add(res, (1ll * C[e + K - 1][K - 1] * S(x / t1, i + 1, K) % mod + C[e + K][K - 1]) % mod);
        }
    }
    return res;
}
inline int G(int x, int K) {
    if (K == 0)
        return 1;
    else if (K == 1)
        return x % mod;
    return S(n, 1, K) + 1;
}

int main() {
    sieve();
    C[0][0] = 1;
    for (int i = 1; i <= 200; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    while (scanf("%d%d", &n, &K) != EOF) {
        if (K == 1)
            printf("%d\n", (n - 1) % mod);
        else if (n < (1 << K))
            puts("0");
        else {
            m = 0;
            blk = sqrt(n);
            //数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
            for (ll i = 1, j; i <= n; i = j + 1) {
                j = n / (n / i);
                w[++m] = n / i;
                g[m] = (mod + w[m] - 1) % mod;
                //记录位置
                if (w[m] <= blk) {
                    id1[w[m]] = m;
                } else {
                    id2[n / w[m]] = m;
                }
            }
            //递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
            // g[i][j]表示的是小于等于i的本身就是质数或者最小质因子大于p_j的所有贡献，省掉的是j那一维
            for (int j = 1; j <= tot; ++j) {
                for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
                    int k = id(w[i] / pri[j]);
                    add(g[i], mod - (g[k] - (j - 1) + mod) % mod);
                }
            }
            int res = 0;
            for (int i = 0, t = ((K & 1) ? -1 : 1); i <= K; ++i, t *= -1) {
                add(res, (mod + 1ll * t * C[K][i] % mod * G(n, i) % mod) % mod);
            }
            res = (res % mod + mod) % mod;
            printf("%d\n", res);
        }
    }
    return 0;
}

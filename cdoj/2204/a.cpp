#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
ll n, mod, w[N << 1], inv2, inv3;
int blk, tot, pri[N], check[N], prik[N][4], sprik[N][4], f[N][4], id1[N], id2[N], m;
inline int id(ll x) {
    if (x <= blk)
        return id1[x];
    return id2[n / x];
}
inline void add(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
inline ll inv(ll x) {
    return qpow(x, mod - 2);
}
void init(int n) {
    memset(check, 0, sizeof check);
    tot = 0;
    for (int i = 2; i <= n; ++i) {
        if (!check[i]) {
            pri[++tot] = i;
            for (int j = 0; j < 4; ++j) {
                prik[tot][j] = qpow(i, j);
                sprik[tot][j] = (sprik[tot - 1][j] + prik[tot][j]) % mod;
            }
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * pri[j] > n)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}
inline ll sum_1(ll x) {
    x %= mod;
    return x * (x + 1) % mod * inv2 % mod;
}
inline ll sum_2(ll x) {
    ll a = x % mod, b = (x + 1) % mod, c = (x * 2 + 1) % mod;
    return a * b % mod * c % mod * inv2 % mod * inv3 % mod;
}
inline ll sum_3(ll x) {
    return sum_1(x) * sum_1(x) % mod;
}

int main() {
    while (scanf("%lld%lld", &n, &mod) != EOF) {
        inv2 = inv(2), inv3 = inv(3);
        m = 0;
        init(blk = sqrt(n));
        //数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
        for (ll i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            w[++m] = n / i;
            f[m][0] = (w[m] + mod - 1) % mod;
            f[m][1] = (sum_1(w[m]) + mod - 1) % mod;
            f[m][2] = (sum_2(w[m]) + mod - 1) % mod;
            f[m][3] = (sum_3(w[m]) + mod - 1) % mod;
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
                for (int o = 0; o < 4; ++o)
                    add(f[i][o], mod - 1ll * prik[j][o] * (f[k][o] - sprik[j - 1][o] + mod) % mod);
            }
        }
        //	cout << f[m][0] << " " << f[m][1] << " " << f[m][2] << " " << f[m][3] << endl;
        for (int i = 1; i < 4; ++i) add(f[1][i], f[1][i - 1]);
        printf("%d\n", f[1][3]);
    }
    return 0;
}

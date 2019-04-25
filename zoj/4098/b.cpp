#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 50;
const ll mod = 1e9 + 7;

struct node {
    int id, num;

    bool operator<(const node &other) {
        return num > other.num;
    }
} p[MAX];

int n, m;
ll w[MAX];
int mp[MAX][MAX];
int vis[MAX];
ll res, sum, k;

ll qpow(ll x, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll inv(ll a) {
    return qpow(a, mod - 2);
}

void DFS(int pos, ll res1, ll res2, ll cnt) {
    if (pos > n) {
        res = (res + res1) % mod;
        sum = (sum + res2) % mod;
        k = (k + cnt) % mod;
        return;
    }
    for (int i = pos + 1; i <= n + 1; ++i) {
        if (vis[p[i].id]) continue;
        if (i == n + 1) {
            DFS(i, res1, res2, cnt);
            break;
        }
        int flag = 0;
        for (int j = i + 1; j <= n; ++j) {
            if (mp[p[i].id][p[j].id]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            DFS(i, (res1 + res1 * w[p[i].id] % mod * w[p[i].id] % mod) % mod, (res2 + res2 * w[p[i].id] % mod) % mod,
                cnt * 2);
            break;
        }
        DFS(i, res1, res2, cnt);
        for (int j = i + 1; j <= n; ++j) {
            if (mp[p[i].id][p[j].id]) {
                vis[p[j].id]++;
            }
        }
        DFS(i, res1 * w[p[i].id] % mod * w[p[i].id] % mod, res2 * w[p[i].id] % mod, cnt);
        for (int j = i + 1; j <= n; ++j) {
            if (mp[p[i].id][p[j].id]) {
                vis[p[j].id]--;
            }
        }
        break;
    }
}

void dfs(int root, ll res1, ll sum1, ll k1) {
    if (root > n) {
        res = (res + res1) % mod;
        sum = (sum + sum1) % mod;
        k += k1;
        return;
    }
    for (int i = root + 1; i <= n + 1; i++) {
        if (vis[p[i].id]) continue;
        if (i == n + 1) {
            dfs(i, res1, sum1, k1);
            break;
        }
        int fg = 0;
        for (int j = i + 1; j <= n; j++) {
            if (mp[p[i].id][p[j].id]) {
                fg = 1;
                break;
            }
        }
        if (fg == 0) {
            dfs(i, (res1 + res1 * w[p[i].id] % mod * w[p[i].id] % mod) % mod, (sum1 + sum1 * w[p[i].id] % mod) % mod,
                k1 * 2);
            break;
        }
        dfs(i, res1, sum1, k1);
        for (int j = i + 1; j <= n; j++) {
            if (mp[p[i].id][p[j].id]) {
                vis[p[j].id]++;
            }
        }
        dfs(i, res1 * w[p[i].id] % mod * w[p[i].id] % mod, sum1 * w[p[i].id] % mod, k1);
        for (int j = i + 1; j <= n; j++) {
            if (mp[p[i].id][p[j].id]) {
                vis[p[j].id]--;
            }
        }
        break;
    }
}

int main() {
//    freopen("Text.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
        w[i] %= mod;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mp[x][y] = mp[y][x] = 1;
    }
    res = 1;
    sum = 1;
    k = 1;
    for (int i = 1; i <= n; i++) {
        p[i].id = i;
        p[i].num = 0;
        for (int j = 1; j <= n; j++) {
            if (mp[i][j]) {
                p[i].num++;
            }
        }
    }
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        for (int j = i + 1; j <= n; j++) {
            if (mp[p[i].id][p[j].id]) {
                vis[p[j].id]++;
            }
        }
        DFS(i, w[p[i].id] * w[p[i].id] % mod, w[p[i].id], 1);
    }
    //公式计算答案
    ll invk = inv(k % mod);
    ll ans = (res * invk % mod - sum * sum % mod * invk % mod * invk % mod + mod) % mod;
    printf("%lld\n", ans);
    return 0;
}

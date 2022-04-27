#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 2e6 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
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
int n, m, G[110][110], p[N], sta[N], top;
void run() {
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; ++j) {
            G[i][j] = s[j - 1] - '0';
        }
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (G[i][j] == 0 && i != j)
                G[i][j] = INF;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    top = 0;
    sta[++top] = p[1];
    for (int i = 2; i <= m; ++i) {
        int now = p[i];
        while (top >= 2) {
            int u = sta[top - 1], v = sta[top];
            if (G[u][now] == G[u][v] + G[v][now])
                --top;
            else
                break;
        }
        sta[++top] = now;
    }
    cout << top << "\n";
    for (int i = 1; i <= top; ++i) cout << sta[i] << " \n"[i == top];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

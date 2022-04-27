#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
}
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
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
constexpr int N = 2e6 + 10;
int n, vis[N], ans, res;
struct node {
    int x[3];
    node() {
        memset(x, -1, sizeof x);
    }
} a[N];
void DFS(int mask, int x) {
    if (a[mask].x[2] != -1) {
        ans = max(ans, mask);
        return;
    }
    bool F = 0;
    for (int i = 0; i < 3; ++i) {
        if (a[mask].x[i] == x)
            return;
        if (a[mask].x[i] == -1) {
            a[mask].x[i] = x;
            F = 1;
            break;
        }
    }
    if (a[mask].x[2] != -1)
        ans = max(ans, mask);
    if (!F)
        return;
    for (int i = 20; i >= 0; --i) {
        if ((mask >> i) & 1) {
            DFS(mask ^ (1 << i), x);
        }
    }
}
void run() {
    memset(vis, 0, sizeof vis);
    memset(a, -1, sizeof a);
    char op[10];
    int x;
    ans = 0;
    res = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> op;
        if (op[0] == 'q') {
            res = ans;
            cout << res << endl;
        } else {
            cin >> x;
            x ^= res;
            if (vis[x])
                continue;
            vis[x] = 1;
            DFS(x, x);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

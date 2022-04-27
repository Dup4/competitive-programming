#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
#define endl "\n"
using VI = vector<int>;
constexpr int N = 3e5 + 10;
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
int n, h, w, fa[N], szep[N], szee[N];
struct node {
    int x, y, w;
    void scan() {
        cin >> x >> y >> w;
        y += h;
    }
    bool operator<(const node &other) const {
        return w > other.w;
    }
} e[N];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void run() {
    for (int i = 1; i <= n; ++i) e[i].scan();
    sort(e + 1, e + 1 + n);
    for (int i = 1; i <= h + w; ++i) {
        fa[i] = i;
        szep[i] = 1;
        szee[i] = 0;
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        int u = find(e[i].x), v = find(e[i].y), w = e[i].w;
        if (u == v) {
            if (szee[u] < szep[u]) {
                res += w;
                ++szee[u];
            }
        } else {
            if (szee[u] + szee[v] < szep[u] + szep[v]) {
                res += w;
                fa[u] = v;
                szee[v] += szee[u];
                ++szee[v];
                szep[v] += szep[u];
            }
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> h >> w) run();
    return 0;
}

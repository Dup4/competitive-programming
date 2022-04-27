#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
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
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
template <class T1, class T2>
T1 gcd(T1 a, T2 b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n;
char s[N];
void run() {
    cin >> n >> (s + 1);
    map<pII, int> mp;
    pII now = pII(0, 0);
    int Min = INF, l = -1, r = -1;
    mp[pII(0, 0)] = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'L')
            ++now.fi;
        else if (s[i] == 'R')
            --now.fi;
        else if (s[i] == 'U')
            ++now.se;
        else
            --now.se;
        if (mp.count(now)) {
            int tl = mp[now] + 1, tr = i;
            if (tr - tl + 1 < Min) {
                Min = tr - tl + 1;
                l = tl;
                r = tr;
            }
        }
        mp[now] = i;
    }
    if (Min == INF)
        pt(-1);
    else
        pt(l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = rd();
    while (_T--) run();
    return 0;
}

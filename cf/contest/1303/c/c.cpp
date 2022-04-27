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
vector<vector<int>> G;
int used[30];
void run() {
    memset(used, 0, sizeof used);
    G.clear();
    G.resize(30);
    string s;
    cin >> s;
    for (int i = 1; i < SZ(s); ++i) {
        int u = s[i - 1] - 'a', v = s[i] - 'a';
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i < 26; ++i) {
        sort(G[i].begin(), G[i].end());
        G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    }
    int one = 0;
    for (int i = 0; i < 26; ++i) {
        if (SZ(G[i]) > 2)
            return pt("NO");
        one += SZ(G[i]) == 1;
    }
    if (SZ(s) == 1) {
        string res;
        for (int i = 0; i < 26; ++i) res += 'a' + i;
        pt("YES");
        cout << res << endl;
    } else if (one == 2) {
        string res;
        int it = -1;
        for (int i = 0; i < 26; ++i) {
            if (SZ(G[i]) == 0) {
                res += 'a' + i;
                used[i] = 1;
            } else if (SZ(G[i]) == 1) {
                it = i;
            }
        }
        used[it] = 1;
        res += 'a' + it;
        while (SZ(res) < 26) {
            for (auto &v : G[it]) {
                if (used[v] == 0) {
                    it = v;
                    break;
                }
            }
            res += 'a' + it;
            used[it] = 1;
        }
        assert(SZ(res) == 26);
        pt("YES");
        cout << res << endl;
    } else {
        pt("NO");
    }
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

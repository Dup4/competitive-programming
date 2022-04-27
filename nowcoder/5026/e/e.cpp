#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr ll mod = 1e9 + 7;
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
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
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
constexpr int N = 2e5 + 10;
int n, K;
char s[N];

struct Hash {
    static ll base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * 131 % mod;
    }
    ll a[N];
    inline void gao(char *s) {
        a[0] = s[0];
        for (int i = 1; s[i]; ++i) {
            a[i] = (a[i - 1] * 131 % mod + s[i]) % mod;
        }
    }
    inline ll get(int l, int r) {
        return (a[r] - a[l - 1] * base[r - l + 1] % mod + mod) % mod;
    }
} hs;
ll Hash::base[N] = {0};

int calc(int x) {
    map<int, vector<int>> mp;
    for (int i = x; i <= n; ++i) {
        mp[hs.get(i - x + 1, i)].push_back(i);
    }
    int res = 0;
    for (auto &it : mp) {
        vector<int> &vec = it.se;
        int now = 0;
        int pre = -1e9;
        for (auto &it : vec) {
            if (pre <= it - x) {
                ++now;
                pre = it;
            }
        }
        chmax(res, now);
    }
    return res;
}

void run() {
    rd(n, K);
    cin >> (s + 1);
    hs.gao(s);
    int l = 1, r = n / K, res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(mid) >= K) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    pt(res);
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}

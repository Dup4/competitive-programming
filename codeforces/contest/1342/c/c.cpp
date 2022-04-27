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
int a, b, q, n;

inline ll get(ll r, ll x) {
    ll res = r / n;
    if (x && r % n >= x)
        ++res;
    return res;
}

void run() {
    rd(a, b, q);
    n = a * b / __gcd(a, b);
    vector<int> vec[2];
    for (int i = 1; i <= n; ++i) {
        int f = (i % a % b != i % b % a);
        vec[f].push_back(i);
    }
    assert(min(SZ(vec[0]), SZ(vec[1])) <= 200);
    int f = SZ(vec[0]) < SZ(vec[1]);
    ll l, r;
    for (int j = 1; j <= q; ++j) {
        rd(l, r);
        ll res = 0;
        if (f) {
            res = r - l + 1;
            for (auto &i : vec[0]) {
                res -= get(r, i) - get(l - 1, i);
            }
        } else {
            for (auto &i : vec[1]) {
                res += get(r, i) - get(l - 1, i);
            }
        }
        cout << res << " ";
    }
    cout << endl;
}

int main() {
    //	int Max = 0;
    //	for (int a = 1; a <= 200; ++a) {
    //		for (int b = 1; b <= 200; ++b) {
    //			int n = a * b / __gcd(a, b);
    //			int cnt = 0;
    //			for (int i = 1; i <= n; ++i) {
    //				cnt += (i % a % b != i % b % a);
    //			}
    //			chmax(Max, min(cnt, n - cnt));
    //		}
    //	}
    //	pt(Max);
    // return 0;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}

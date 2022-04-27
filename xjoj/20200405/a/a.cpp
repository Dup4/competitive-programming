#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
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
constexpr int N = 1e5 + 10;
int n;

vector<pII> vec;

void run() {
    vec.clear();
    if (n == 2) {
        pt(5);
        pt(1, 1);
        pt(1, 2);
        pt(1, 3);
        pt(2, 3);
        pt(2, 2);
        pt(2, 1);
    } else if (n == 3) {
        pt(11);
        pt(1, 4);
        pt(2, 3);
        pt(1, 2);
        pt(2, 1);
        pt(1, 1);
        pt(2, 2);
        pt(1, 3);
        pt(2, 4);
        pt(3, 4);
        pt(3, 3);
        pt(3, 2);
        pt(3, 1);
    } else {
        if (n & 1) {
            for (int i = 1; i <= n; i += 2) {
                if (i == n) {
                    for (int j = n + 1; j >= 1; --j) vec.emplace_back(i, j);
                } else {
                    for (int j = n + 1; j >= 1; --j) {
                        int dis = (n + 1 - j);
                        if (dis % 2 == 0)
                            vec.emplace_back(i, j);
                        else
                            vec.emplace_back(i + 1, j);
                    }
                    for (int j = 1; j <= n + 1; ++j) {
                        int dis = j - 1;
                        if (dis % 2 == 0)
                            vec.emplace_back(i, j);
                        else
                            vec.emplace_back(i + 1, j);
                    }
                }
            }
        } else {
            for (int i = n; i >= 1; i -= 2) {
                for (int j = 2; j <= n + 1; ++j) {
                    int dis = j - 2;
                    if (dis % 2 == 0)
                        vec.emplace_back(i, j);
                    else
                        vec.emplace_back(i - 1, j);
                }
                for (int j = n + 1; j >= 1; --j) {
                    int dis = (n + 1 - j);
                    if (dis % 2 == 0)
                        vec.emplace_back(i, j);
                    else
                        vec.emplace_back(i - 1, j);
                }
                vec.emplace_back(i - 1, 1);
            }
        }
        pt(SZ(vec) - 1);
        for (auto &it : vec) pt(it.fi, it.se);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}

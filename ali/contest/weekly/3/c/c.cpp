#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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

ll calc(int n) {
    if (n == 0)
        return 1;
    ll res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= 2;
        if (res >= 1e18)
            break;
    }
    return res;
}

class Solution {
public:
    /**
     * @param n: the length of the string.
     * @param k: the kth Lexicographically smallest that result should be.
     * @return: return the kth Lexicographically smallest string.
     */
    string kthString(int n, long long k) {
        // write your code here.
        if (3ll * calc(n - 1) < k)
            return "";
        string s = "", t = "";
        for (int i = 1; i <= n; ++i) {
            if (i == 1)
                t = "def";
            else {
                t = "";
                string tmp = "def";
                for (auto &it : tmp) {
                    //		dbg(s.back(), it);
                    if (s.back() != it)
                        t += it;
                }
                //	dbg(t);
            }
            //	reverse(all(t));
            int sz = SZ(t);
            for (int j = sz - 1; j >= 0; --j) {
                ll f = 1ll * j * calc(n - i);
                if (k > f || !j) {
                    k -= f;
                    s += t[j];
                    break;
                }
            }
        }
        return s;
    }
};

void run() {
    int n;
    ll k;
    rd(n, k);
    pt((new Solution())->kthString(n, k));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    // nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}

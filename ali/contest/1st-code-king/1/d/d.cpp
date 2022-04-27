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
constexpr int N = 3e3 + 10;
int n, m;
char s[N], t[N];

struct ExKMP {
    int Next[N], extend[N];
    // 1-index
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        // Next[1]要特殊考虑
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        // Next[2]初始化
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            //第一种情况
            if (len + i < p + 1)
                Next[i] = len;
            //第二种情况
            else {
                //找到对于子串最靠后已经匹配的位置
                int j = max(p - i + 1, 0);
                //暴力匹配
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }
    void work(char *s, char *t) {
        memset(Next, 0, sizeof Next);
        memset(extend, 0, sizeof extend);
        get_Next(t);
        int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
        while (p <= lent && s[p] == t[p]) ++p;
        p = extend[pos = 1] = p - 1;
        for (int i = 2; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
                p = i + (extend[pos = i] = j) - 1;
            }
        }
    }
} exkmp;

class Solution {
public:
    /**
     * @param s: a string.
     * @return: return the values of all the intervals.
     */
    long long suffixQuery(string &str) {
        // write your code here
        ll res = 0;
        m = SZ(str);
        for (int i = 1; i <= m; ++i) {
            n = m - i + 1;
            for (int j = 1; j <= n; ++j) {
                t[j] = s[j] = str[i + j - 2];
            }
            s[n + 1] = t[n + 1] = 0;
            reverse(t + 1, t + 1 + n);
            exkmp.work(t, s);
            //	cout << (s + 1) << endl;
            //	cout << (t + 1) << endl;
            for (int j = 1; j <= n; ++j) {
                //		dbg(i, j, exkmp.extend[j]);
                res += exkmp.extend[j];
            }
            //	if (i == 1) {
            //		cout << (s + 1) << endl;
            //		cout << (t + 1) << endl;
            //		exkmp.work(s, t);
            //		for (int j = 1; j <= n; ++j) {
            //			dbg(j, exkmp.extend[j]);
            //		}
            //	}
        }
        return res;
    }
};

void run() {
    string s;
    rd(s);
    pt((new Solution)->suffixQuery(s));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    // nextInt();
    while (_T--) run();
    return 0;
}

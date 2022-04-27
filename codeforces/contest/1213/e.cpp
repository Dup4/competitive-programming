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
constexpr int N = 1e5 + 10;
int n;
string s, t, res;
bool ok(string ss) {
    for (int i = 0; i < 2; ++i) {
        string now = "";
        now += ss[i];
        now += ss[i + 1];
        if (now == s or now == t)
            return false;
    }
    return true;
}
void run() {
    cin >> s >> t;
    out("YES");
    res = "";
    if (s[0] == s[1] and t[0] == t[1]) {
        for (int i = 0; i < n; ++i) {
            res += "abc";
        }
    } else if (s[0] == s[1] or t[0] == t[1]) {
        if (s[0] != s[1])
            swap(s, t);
        string tmp = "";
        swap(t[0], t[1]);
        tmp += t;
        for (char it : {'a', 'b', 'c'}) {
            if (it != tmp[0] and it != tmp[1])
                tmp += it;
        }
        for (int i = 0; i < n; ++i) res += tmp;
    } else {
        string tmp = "abc";
        do {
            if (ok(tmp))
                break;
        } while (next_permutation(tmp.begin(), tmp.end()));
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < n; ++j) res += tmp[i];
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

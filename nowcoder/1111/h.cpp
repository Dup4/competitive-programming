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
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
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
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
constexpr int N = 1e6 + 10;
int n, m, a[N], b[N], S[N];
vector<pII> vec;
inline int get(int l, int r) {
    if (l > r)
        return 0;
    return S[r] - S[l - 1];
}
ll gao(int *a, int n, int *b, int m) {
    memset(S, 0, sizeof S);
    for (int i = 1; i <= n; ++i) ++S[a[i]];
    for (int i = 1; i < N; ++i) S[i] += S[i - 1];
    ll res = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0, sze = vec.size(); j < sze; ++j) {
            int l = vec[j].fi, r = vec[j].se;
            if (l > b[i])
                break;
            int ql = max(0, b[i] - r), qr = min(1000000, b[i] - l);
            res += 1ll * j * get(ql, qr);
        }
    }
    return res;
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    pt(gao(a, n, b, m) + gao(b, m, a, n));
}

int main() {
    vec.clear();
    vec.push_back(pII(0, 0));
    for (int i = 1; i <= 1001; ++i) {
        vec.push_back(pII(i * i, (i + 1) * (i + 1) - 1));
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}

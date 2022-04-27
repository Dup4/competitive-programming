#include <bits/stdc++.h>
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << " ";
    pt(args...);
}
template <class T>
inline void pt(const T &s) {
    cout << s << "\n";
}
template <class T>
inline void pt(const vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
ll gcd(ll a, ll b) {
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
constexpr int N = 3e5 + 10;
mt19937 rnd(time(0));
//
ull B[] = {1572869, 3145739, 6291469, 12582917, 25165843, 50331653};
ull BB;
struct Hash {
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * BB;
    }
    ull a[N];
    inline void work() {
        a[0] = 0;
    }
    inline void add(int ch, int id) {
        a[id] = a[id - 1] * BB + ch;
    }
} hs;
ull Hash::base[N] = {0};
map<ull, int> mp;
int n, a[N], sta[N];
void run() {
    BB = B[rnd() % 6];
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    mp.clear();
    mp[0] = 1;
    *sta = 0;
    ll res = 0;
    hs.work();
    for (int i = 1; i <= n; ++i) {
        if (*sta && sta[*sta] == a[i])
            --*sta;
        else
            sta[++*sta] = a[i], hs.add(a[i], *sta);
        ull H = hs.a[*sta];
        res += mp[H];
        ++mp[H];
    }
    pt(res);
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}

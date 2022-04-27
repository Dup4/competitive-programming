#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
#define endl "\n"
constexpr int N = 2e5 + 10;
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
inline void out(T s) {
    cout << s << "\n";
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
int n, a[N];
ll s[N];
struct SEG {
    ll t[N << 2];
    void up(int id) {
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        up(id);
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        up(id);
    }
    int query(int id, int l, int r, ll s) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (t[id << 1] > s)
            return query(id << 1, l, mid, s);
        else
            return query(id << 1 | 1, mid + 1, r, s - t[id << 1]);
    }
} seg;
void run() {
    for (int i = 1; i <= n; ++i) cin >> s[i];
    seg.build(1, 1, n);
    for (int i = n; i >= 1; --i) {
        a[i] = seg.query(1, 1, n, s[i]);
        seg.update(1, 1, n, a[i]);
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

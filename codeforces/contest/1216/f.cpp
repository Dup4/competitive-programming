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
constexpr int N = 2e5 + 10;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, k;
char s[N];
struct SEG {
    ll t[N << 2];
    void build(int id, int l, int r) {
        t[id] = INF;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (l >= ql && r <= qr) {
            t[id] = min(t[id], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    ll query(int id, int l, int r, int pos) {
        ll res = t[id];
        if (l == r)
            return res;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            res = min(res, query(id << 1, l, mid, pos));
        else
            res = min(res, query(id << 1 | 1, mid + 1, r, pos));
        return res;
    }
} seg;
void run() {
    cin >> (s + 1);
    seg.build(1, 0, n);
    seg.update(1, 0, n, 0, 0, 0);
    for (int i = 1, j = 1; i <= n; ++i) {
        seg.update(1, 0, n, i, i, seg.query(1, 0, n, i - 1) + i);
        while (j - i <= k && j <= n) {
            if (s[j] == '1') {
                seg.update(1, 0, n, i, min(j + k, n), seg.query(1, 0, n, i - 1) + j);
            }
            ++j;
        }
    }
    out(seg.query(1, 0, n, n));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k) run();
    return 0;
}

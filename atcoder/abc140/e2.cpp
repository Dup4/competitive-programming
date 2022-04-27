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
int n, a[N], sta[N];
pII pre[N], nx[N];
vector<vector<int>> qvec;
int get(int x) {
    int l = 1, r = *sta, res = -1;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (sta[mid] > a[i]) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res == -1 ? -1 : sta[res];
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    *sta = 0;
    memset(pre, -1, sizeof pre);
    memset(nx, -1, sizeof nx);
    for (int i = n; i >= 1; --i) {
        int p = get(a[i]);
        if (p != -1) {
            nx[i].fi = p;
            qvec[p].push_back(i);
        }
        if (!*sta || a[i] > sta[*sta])
            sta[++*sta] = a[i];
    }
    *sta = 0;
    for (int i = n; i >= 1; --i) {
        for (auto &it : qvec[i]) {
            int p = get(a[it]);
            if (p != -1) {
                nx[it].se = p;
            }
        }
        if (!*sta || a[i] > sta[*sta])
            sta[++*sta] = a[i];
    }
    *sta = 0;
    for (int i = 1; i <= n; ++i) {
        int p = get(a[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

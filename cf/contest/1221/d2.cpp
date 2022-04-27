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
constexpr int N = 3e5 + 10;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, a[N], b[N];
pLL c[2];
void run() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    c[0] = pLL(0, a[1]);
    c[1] = pLL(b[1], a[1] + 1);
    for (int i = 2; i <= n; ++i) {
        vector<pLL> vec;
        int it = a[i];
        ll fee = 0;
        while (vec.size() < 20) {
            if (it != c[0].se)
                vec.push_back(pLL(c[0].fi + fee, it));
            else if (it != c[1].se)
                vec.push_back(pLL(c[1].fi + fee, it));
            ++it;
            fee += b[i];
        }
        sort(vec.begin(), vec.end(), [&](pLL x, pLL y) {
            return x.fi < y.fi;
        });
        c[0] = vec[0];
        c[1] = vec[1];
        //	cout << c[0].fi << " " << c[0].se << endl;
        //	cout << c[1].fi << " " << c[1].se << endl;
    }
    cout << c[0].fi << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}

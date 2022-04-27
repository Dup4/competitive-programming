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
constexpr int N = 1e5 + 10;
int n;
ll res;
pII a[N];
inline void scan(pII &a) {
    int l, d;
    string s;
    cin >> l >> s >> d;
    if (s[0] == '(')
        res += 1ll * l * d, d = -d;
    a = pII(l, d);
}
void run() {
    res = 0;
    for (int i = 1; i <= n; ++i) scan(a[i]);
    ll tot = 0, has = 0;
    priority_queue<pII, vector<pII>, greater<pII>> pq;
    for (int i = 1; i <= n; ++i) {
        tot += a[i].fi;
        ll need = ((tot + 1) / 2) - has;
        //	cout << need << endl;
        has += need;
        pq.push(pII(a[i].se, a[i].fi));
        while (!pq.empty()) {
            pII t = pq.top();
            pq.pop();
            if (t.se >= need) {
                t.se -= need;
                res += 1ll * need * t.fi;
                pq.push(t);
                break;
            } else {
                need -= t.se;
                res += 1ll * t.fi * t.se;
            }
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

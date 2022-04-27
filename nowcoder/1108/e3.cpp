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
const int N = 1e5 + 10;
int n, m, q, num[2];
set<pII> se[2];
bool cross(pII x, pII y) {
    if ((x.fi >= y.fi && x.fi <= y.se) || (x.se >= y.fi && x.se <= y.se) || (y.fi >= x.fi && y.fi <= x.se) ||
            (y.se >= x.fi && y.se <= x.se))
        return true;
    return false;
}
void ins(int id, int l, int r) {
    pII t = pII(l, r);
    if (se[id].empty()) {
        se[id].insert(t);
        num[id] += r - l + 1;
    } else {
        auto pos = se[id].lower_bound(t);
        vector<pII> vec, tmp;
        if (pos != se[id].begin()) {
            --pos;
        }
        while (pos != se[id].end()) {
            if (cross(*pos, t)) {
                vec.push_back(*pos);
            }
            if ((*pos).fi > t.se)
                break;
            ++pos;
        }
        for (auto &it : vec) {
            se[id].erase(it);
            num[id] -= it.se - it.fi + 1;
        }
        vec.push_back(t);
        sort(vec.begin(), vec.end(), [&](pII x, pII y) {
            if (x.fi == y.fi)
                return x.se > y.se;
            return x.fi < y.fi;
        });
        for (auto &it : vec) {
            if (tmp.empty())
                tmp.push_back(it);
            else {
                if (it.fi <= tmp.end()[-1].se)
                    chmax(tmp.end()[-1].se, it.se);
                else
                    tmp.push_back(it);
            }
        }
        for (auto &it : tmp) {
            num[id] += it.se - it.fi + 1;
            se[id].insert(it);
        }
    }
}
void run() {
    num[0] = num[1] = 0;
    se[0].clear();
    se[1].clear();
    ll a = 0, b = 0;
    for (int i = 1, op, l, r; i <= q; ++i) {
        cin >> op >> l >> r;
        ins(op - 1, l, r);
        a = num[0], b = num[1];
        ll res = 1ll * n * m;
        if (a == 0) {
            res -= b * (n - 1);
        } else if (b == 0) {
            res -= a * (m - 1);
        } else {
            res -= a * m + b * n - a * b;
            ++res;
        }
        pt(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> q) run();
    return 0;
}

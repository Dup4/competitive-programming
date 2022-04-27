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
constexpr int N = 1e6 + 10;
int n, k;
ll L[N], W[N], H[N];

struct E {
    ll l, r, h;
    E() {}
    E(ll l, ll r, ll h) : l(l), r(r), h(h) {}
    bool operator<(const E &other) const {
        return l < other.l;
    }
} e[N];

void run() {
    rd(n, k);
    for (auto &it : {L, W, H}) {
        for (int i = 1; i <= k; ++i) rd(it[i]);
        ll A, B, C, D;
        rd(A, B, C, D);
        for (int i = k + 1; i <= n; ++i) {
            it[i] = ((A * it[i - 2] + B * it[i - 1]) + C) % D + 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        e[i] = E(L[i], L[i] + W[i], H[i]);
        //		dbg(i, H[i]);
        //	dbg(i, L[i], W[i], H[i]);
    }
    ll res = 1;
    ll width = 0, height = 0;
    set<E> se;
    for (int i = 1; i <= n; ++i) {
        ll l = e[i].l, r = e[i].r, h = e[i].h;
        //	dbg(i, l, r, h);
        if (se.empty()) {
            se.insert(E(l, r, h));
            chadd(width, (r - l) * 2);
            chadd(height, h * 2);
        } else {
            auto pos = se.upper_bound(E(l, l, 0));
            if (pos != se.begin())
                pos = prev(pos);
            vector<E> vec;
            while (pos != se.end()) {
                auto nx = next(pos);
                if ((pos->l >= l && pos->l <= r) || (pos->r >= l && pos->r <= r) || (l >= pos->l && l <= pos->r) ||
                        (r >= pos->l && r <= pos->r)) {
                    vec.push_back(*pos);
                    se.erase(pos);
                    pos = nx;
                } else {
                    if (pos->l > r)
                        break;
                    else
                        pos = nx;
                }
            }
            if (vec.empty()) {
                se.insert(E(l, r, h));
                chadd(width, (r - l) * 2);
                chadd(height, h * 2);
            } else {
                ll _l = l, _r = r;
                for (auto &it : vec) {
                    chmin(_l, it.l);
                    chmax(_r, it.r);
                    chadd(width, mod - (it.r - it.l) * 2 % mod);
                    //	width -= (it.r - it.l + 1) * 2;
                }
                //	dbg(i, SZ(vec), (SZ(vec) - 1));
                chadd(height, mod - 1ll * (SZ(vec) - 1) * 2 % mod * h % mod);
                chadd(width, (_r - _l) * 2 % mod);
                se.insert(E(_l, _r, h));
            }
        }
        // dbg(i, width, height);
        res = (res * ((width + height) % mod)) % mod;
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    //	while (_T--) run();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}

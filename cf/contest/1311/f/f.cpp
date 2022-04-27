#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
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
constexpr int N = 2e5 + 10;
int n;
pII a[N];

template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct map_node_update {
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    typedef long long metadata_type;
    const static int INF = 0x3f3f3f3f;
    void operator()(Node_Itr it, Node_CItr end_it) {
        Node_Itr l = it.get_l_child();
        Node_Itr r = it.get_r_child();
        metadata_type left = 0, right = 0;
        if (l != end_it)
            left = l.get_metadata();
        if (r != end_it)
            right = r.get_metadata();
        const_cast<metadata_type &>(it.get_metadata()) = left + right + (*it)->second;
    }
    metadata_type querysum(pII x) {
        metadata_type ans = 0;
        Node_CItr it = node_begin();
        while (it != node_end()) {
            Node_CItr l = it.get_l_child();
            Node_CItr r = it.get_r_child();
            if (Cmp_Fn()(x, (*it)->first)) {
                it = l;
            } else {
                ans += (*it)->second;
                if (l != node_end())
                    ans += l.get_metadata();
                it = r;
            }
        }
        return ans;
    }
    metadata_type querysum(int l, int r) {
        if (l > r)
            return 0;
        return querysum(pII(r, INF)) - querysum(pII(l, -INF));
    }
};
tree<pII, int, less<pII>, rb_tree_tag, map_node_update> rbt[2];

void run() {
    for (int i = 1; i <= n; ++i) rd(a[i].fi);
    for (int i = 1; i <= n; ++i) rd(a[i].se);
    sort(a + 1, a + 1 + n);
    ll res = 0;
    rbt[0].clear();
    rbt[1].clear();
    int limit = 1e8 + 10;
    for (int i = n; i >= 1; --i) {
        ll now = rbt[0].querysum(a[i].se, limit) - rbt[1].querysum(a[i].se, limit) * a[i].fi;
        res += now;
        rbt[0].insert(make_pair(pII(a[i].se, i), a[i].fi));
        rbt[1].insert(make_pair(pII(a[i].se, i), 1));
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}

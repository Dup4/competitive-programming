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
int n, q, a[N];
struct Mo {
    //计数
    int cnt[N];
    //块大小
    int block;
    //询问数和操作数
    int cnt_qu;
    //储存答案
    ll res, ans[N];
    struct Query {
        int id, l, r, bl, br;
        Query() {}
        Query(int id, int l, int r, int bl, int br) : id(id), l(l), r(r), bl(bl), br(br) {}
        bool operator<(const Query &other) const {
            if (bl != other.bl)
                return bl < other.bl;
            if (bl & 1)
                return br < other.br;
            else
                return br > other.br;
        }
    } qu[N];
    void init(int n) {
        //设置块的大小
        block = sqrt(n);
        cnt_qu = 0;
        res = 0;
    }
    void addquery(int l, int r) {
        if (l > r)
            swap(l, r);
        ++cnt_qu;
        qu[cnt_qu] = Query(cnt_qu, l, r, l / block, r / block);
    }
    void update(int id, int opt) {
        res -= 1ll * a[id] * cnt[a[id]] * cnt[a[id]];
        cnt[a[id]] += opt;
        res += 1ll * a[id] * cnt[a[id]] * cnt[a[id]];
    }
    void work() {
        sort(qu + 1, qu + 1 + cnt_qu);
        for (int i = 1, l = 1, r = 0; i <= cnt_qu; ++i) {
            for (; r < qu[i].r; ++r) update(r + 1, 1);
            for (; r > qu[i].r; --r) update(r, -1);
            for (; l > qu[i].l; --l) update(l - 1, 1);
            for (; l < qu[i].l; ++l) update(l, -1);
            ans[qu[i].id] = res;
        }
        for (int i = 1; i <= cnt_qu; ++i) cout << ans[i] << endl;
    }
    //多组数据记得清空
    void clear(int n) {
        for (int i = 0; i <= n; ++i) cnt[i] = 0;
    }
} mo;
void run() {
    mo.init(n);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= q; ++i) mo.addquery(rd(), rd());
    mo.work();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}

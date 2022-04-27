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
constexpr int N = 1e6 + 10;
int n, q;
mt19937 rnd(time(0));
struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, rnd, sze, rev;
    } t[N];
    int tot, rt[N], seed;
    inline void init() {
        seed = 703;
        tot = 0;
        for (int i = 0; i <= n; ++i) rt[i] = 0;
    }
    inline void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
    }
    inline void pushdown(int x) {
        if (x && t[x].rev) {
            t[x].rev ^= 1;
            swap(t[x].son[0], t[x].son[1]);
            t[ls].rev ^= 1;
            t[rs].rev ^= 1;
        }
    }
    inline int random() {
        return seed = int(seed * 48217ll % 2147483647);
    }
    inline int newnode(int key) {
        ++tot;
        t[tot].sze = 1;
        t[tot].key = key;
        t[tot].rnd = random();
        t[tot].rev = t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd) {
            pushdown(x);
            t[x].son[1] = merge(t[x].son[1], y);
            pushup(x);
            return x;
        } else {
            pushdown(y);
            t[y].son[0] = merge(x, t[y].son[0]);
            pushup(y);
            return y;
        }
    }
    void split(int now, int k, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            pushdown(now);
            if (k <= t[t[now].son[0]].sze) {
                y = now;
                split(t[now].son[0], k, x, t[now].son[0]);
            } else {
                x = now;
                split(t[now].son[1], k - t[t[now].son[0]].sze - 1, t[now].son[1], y);
            }
            pushup(now);
        }
    }
    inline void insert(int id, int key) {
        if (rt[id] == 0) {
            rt[id] = newnode(key);
        } else {
            rt[id] = merge(rt[id], newnode(key));
        }
    }
    inline void rev(int id) {
        t[rt[id]].rev ^= 1;
    }
    inline void print(int x) {
        if (!x)
            return;
        pushdown(x);
        print(ls);
        cout << " " << t[x].key;
        print(rs);
    }
} fhq;

void run() {
    fhq.init();
    for (int i = 1; i <= n; ++i) fhq.insert(i, i);
    for (int i = 1, a, b; i <= q; ++i) {
        cin >> a >> b;
        fhq.rt[a] = fhq.merge(fhq.rt[a], fhq.rt[b]);
        fhq.rt[b] = 0;
        fhq.rev(a);
    }
    cout << fhq.t[fhq.rt[1]].sze;
    fhq.print(fhq.rt[1]);
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}

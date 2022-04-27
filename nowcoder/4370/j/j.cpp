#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
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
constexpr int N = 2e6 + 10;
int n, m;
ll ten[20];
vector<ll> A;

inline ll add(ll a, ll b) {
    ll bit = 1;
    ll res = 0;
    for (; a || b;) {
        res += (a % 10 + b % 10) % 10 * bit;
        a /= 10;
        b /= 10;
        bit *= 10;
    }
    return res;
}

inline ll sub(ll a, ll b) {
    ll bit = 1;
    ll res = 0;
    for (; a || b;) {
        res += (a % 10 - b % 10 + 10) % 10 * bit;
        a /= 10;
        b /= 10;
        bit *= 10;
    }
    return res;
}

struct Trie {
    struct node {
        int son[10], fa;
        ll sum;
        int lazy;
        node() {}
        void init() {
            memset(son, 0, sizeof son);
            sum = lazy = fa = 0;
        }
    } t[N];
    int cnt, rt;
    vector<int> leaf;
    int newnode() {
        ++cnt;
        t[cnt].init();
        return cnt;
    }
    void init() {
        cnt = 0;
        rt = newnode();
        leaf.clear();
    }
    void pushdown(int id) {
        int &lazy = t[id].lazy;
        lazy = min(lazy, 10);
        if (!t[id].lazy)
            return;
        for (int i = 0; i < 10; ++i) {
            int son = t[id].son[i];
            if (son) {
                t[son].sum /= ten[lazy];
                t[son].lazy += lazy;
            }
        }
        lazy = 0;
    }
    void insert(ll x) {
        int root = rt;
        t[root].sum = add(t[root].sum, x);
        for (int i = 9; i >= 0; --i) {
            int now = (x / ten[i]) % 10;
            pushdown(root);
            if (!t[root].son[now]) {
                t[root].son[now] = newnode();
                t[t[root].son[now]].fa = root;
            }
            root = t[root].son[now];
            t[root].sum = add(t[root].sum, x);
            if (i == 0 && root == cnt) {
                leaf.push_back(root);
            }
        }
    }
    ll queryMax(ll x) {
        int root = rt;
        ll res = 0;
        for (int i = 9; i >= 0; --i) {
            int now = (x / ten[i]) % 10;
            pushdown(root);
            int ok = 0;
            for (int j = 9; j >= 0; --j) {
                int tar = (j - now + 10) % 10;
                if (t[root].son[tar]) {
                    ok = 1;
                    res += ten[i] * j;
                    root = t[root].son[tar];
                    break;
                }
            }
            if (!ok)
                break;
        }
        return res;
    }
    ll querySum(ll x) {
        int root = rt;
        ll res = 0;
        for (int i = 9; i >= 0; --i) {
            int now = (x / ten[i]) % 10;
            pushdown(root);
            for (int j = 0; j < now; ++j)
                if (t[root].son[j]) {
                    res = add(res, t[t[root].son[j]].sum);
                }
            if (t[root].son[now] == 0)
                break;
            root = t[root].son[now];
        }
        return res;
    }
    void build(const vector<ll> &vec) {
        init();
        for (auto &it : vec) insert(it);
    }
    void shift() {
        int nxroot = newnode();
        t[nxroot].sum = t[rt].sum / 10;
        t[nxroot].lazy = 1;
        t[nxroot].son[0] = rt;
        t[rt].fa = nxroot;
        rt = nxroot;
        vector<int> tmp;
        for (auto &it : leaf) {
            tmp.push_back(t[it].fa);
            for (int i = 0; i < 10; ++i)
                if (t[t[it].fa].son[i] == it) {
                    t[t[it].fa].son[i] = 0;
                    break;
                }
        }
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        leaf = tmp;
    }
} trie;

void run() {
    rd(n, m);
    A.clear();
    for (int i = 1, x; i <= n; ++i) {
        rd(x);
        A.push_back(x);
    }
    trie.build(A);
    string op;
    int x, l, r;
    while (m--) {
        rd(op);
        if (op == "Add") {
            rd(x);
            trie.insert(x);
        } else if (op == "Shift") {
            trie.shift();
        } else if (op == "Query") {
            rd(x);
            pt(trie.queryMax(x));
        } else {
            rd(l, r);
            pt(sub(trie.querySum(r + 1), trie.querySum(l)));
        }
    }
}

int main() {
    ten[0] = 1;
    for (int i = 1; i <= 10; ++i) ten[i] = ten[i - 1] * 10;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    //	while (_T--) run();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ":\n";
        run();
    }
    //	while (cin >> n) run();
    return 0;
}

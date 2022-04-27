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
constexpr int N = 5e5 + 10;
int n, q, rk[N];

struct Tree {
    struct node {
        int rk, id;
        int dep, sumD, lazyD;
        int ls, rs, sze;
        node() {}
        node(int _rk, int _id, int _dep) {
            rk = _rk;
            id = _id;
            dep = sumD = _dep;
            lazyD = 0;
            ls = rs = 0;
            sze = 1;
        }
        void up(int _lazy) {
            dep += _lazy;
            sumD += sze * _lazy;
            lazyD += _lazy;
        }
        void init() {
            ls = rs = sze = 0;
            dep = sumD = lazyD = 0;
        }
    } t[N];
    int cnt, rt;
    void init() {
        cnt = 0;
        t[0].init();
        rt = 0;
    }
    int newnode() {
        ++cnt;
        t[cnt].init();
        return cnt;
    }
    void up(int id) {
        int ls = t[id].ls, rs = t[id].rs;
        t[id].sumD = t[id].dep;
        t[id].sze = 1;
        if (ls) {
            t[id].sumD += t[ls].sumD;
            t[id].sze += t[ls].sze;
        }
        if (rs) {
            t[id].sumD += t[rs].sumD;
            t[id].sze += t[rs].sze;
        }
    }
    void down(int id) {
        int &lazy = t[id].lazyD;
        if (!lazy)
            return;
        int ls = t[id].ls, rs = t[id].rs;
        if (ls)
            t[ls].up(lazy);
        if (rs)
            t[rs].up(lazy);
        lazy = 0;
    }
    void insert(int &rt, int rk, int id, int dep) {
        if (rt == 0) {
            int now = newnode();
            t[now] = node(rk, id, dep);
            rt = now;
            return;
        }
        down(rt);
        if (id < t[rt].id) {
            if (rk < t[rt].rk)
                insert(t[rt].ls, rk, id, dep + 1);
            else
                insert(t[rt].rs, rk, id, dep + 1);
        } else {
            int now = newnode();
            t[now] = node(rk, id, dep);
            if (rk < t[rt].rk) {
                t[now].rs = rt;
                if (t[rt].ls) {
                    t[now].ls = t[rt].ls;
                    t[rt].ls = 0;
                }
                t[rt].up(1);
            } else {
                t[now].ls = rt;
                if (t[rt].rs) {
                    t[now].rs = t[rt].rs;
                    t[rt].rs = 0;
                }
                t[rt].up(1);
            }
            rt = now;
        }
        up(rt);
    }
    void merge(int &rt, int ls, int rs) {
        down(rt);
        if (ls == 0 || rs == 0) {
            rt = ls | rs;
        } else {
            if (t[ls].id > t[rs].id) {
                rt = ls;
                t[rs].up(1);
                down(rs);
                if (t[rs].rk < t[ls].rk) {
                    merge(t[ls].ls, t[ls].ls, rs);
                } else {
                    merge(t[ls].rs, t[ls].rs, rs);
                }
            } else {
                rt = rs;
                t[ls].up(1);
                down(ls);
                if (t[ls].rk < t[rs].rk) {
                    merge(t[rs].ls, t[rs].ls, ls);
                } else {
                    merge(t[rs].rs, t[rs].rs, ls);
                }
            }
        }
        up(rt);
    }
    void del(int &rt, int rk) {
        down(rt);
        if (t[rt].rk == rk) {
            int ls = t[rt].ls, rs = t[rt].rs;
            if (ls == 0 && rs == 0) {
                rt = 0;
            } else if (ls == 0) {
                t[rs].up(-1);
                rt = rs;
            } else if (rs == 0) {
                t[ls].up(-1);
                dbg(t[ls].id, t[ls].sumD);
                rt = ls;
            } else {
                if (t[ls].id > t[rs].id) {
                    rt = ls;
                    t[ls].up(-1);
                    merge(t[ls].rs, t[ls].rs, rs);
                } else {
                    rt = rs;
                    t[rs].up(-1);
                    merge(t[rs].ls, t[rs].ls, ls);
                }
            }
        } else {
            if (rk > t[rt].rk)
                del(t[rt].rs, rk);
            else
                del(t[rt].ls, rk);
            up(rt);
        }
        dbg(rt, t[rt].rk, t[rt].id, t[rt].sumD, t[t[rt].ls].id, t[t[rt].rs].id, t[t[rt].ls].sumD, t[t[rt].rs].sumD);
    }
    void print(int rt) {
        if (!rt)
            return;
        down(rt);
        print(t[rt].ls);
        //	dbg(t[rt].id, t[rt].rk, t[rt].dep, t[rt].sze, t[t[rt].ls].id, t[t[rt].rs].id);
        print(t[rt].rs);
        up(rt);
    }
} tree;

void run() {
    rd(n, q);
    for (int i = 1; i <= n; ++i) rd(rk[i]);
    tree.init();
    for (int i = n; i >= 1; --i) tree.insert(tree.rt, rk[i], i, 1);
    dbg(tree.rt, tree.t[tree.rt].sumD);
    tree.print(tree.rt);
    //	return;
    for (int i = 1, x; i <= q; ++i) {
        rd(x);
        int pre = tree.t[tree.rt].sumD;
        tree.del(tree.rt, rk[x]);

        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);
        tree.print(tree.rt);
        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);

        tree.del(tree.rt, rk[x + 1]);

        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);
        tree.print(tree.rt);
        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);

        swap(rk[x], rk[x + 1]);
        tree.insert(tree.rt, rk[x], x, 1);

        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);
        tree.print(tree.rt);
        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);

        tree.insert(tree.rt, rk[x + 1], x + 1, 1);

        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);
        tree.print(tree.rt);
        dbg(tree.t[tree.rt].id, tree.t[tree.rt].sumD);

        //	dbg(tree.t[tree.rt].sumD, pre);
        pt(abs(tree.t[tree.rt].sumD - pre));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}

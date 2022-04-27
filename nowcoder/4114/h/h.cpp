#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, a[N], b[N], c[N], d[N];
ll res;
vector<vector<int>> fac;

inline ll f(ll x) {
    return x * (x + 1) / 2;
}

struct SEG {
    struct node {
        ll sum;
        int Min[2], num, cnt, lazy;
        node() {
            num = sum = cnt = 0;
            Min[0] = INF;
            Min[1] = INF;
            lazy = -INF;
        }
        void add(int x) {
            if (x <= Min[0])
                return;
            sum += 1ll * num * (x - Min[0]);
            Min[0] = x;
            lazy = x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.cnt = cnt + other.cnt;
            if (Min[0] == other.Min[0]) {
                res.Min[0] = Min[0];
                res.num = num + other.num;
                if (res.num != res.cnt) {
                    res.Min[1] = min(Min[1], other.Min[1]);
                } else {
                    res.Min[1] = INF;
                }
            } else {
                if (Min[0] < other.Min[0]) {
                    res.Min[0] = Min[0];
                    res.Min[1] = min(Min[1], other.Min[0]);
                    res.num = num;
                } else {
                    res.Min[0] = other.Min[0];
                    res.Min[1] = min(other.Min[1], Min[0]);
                    res.num = other.num;
                }
            }
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].cnt = t[id].num = 1;
            t[id].Min[0] = t[id].sum = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id) {
        int &lazy = t[id].lazy;
        if (lazy == -INF)
            return;
        t[id << 1].add(lazy);
        t[id << 1 | 1].add(lazy);
        lazy = -INF;
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
        if (ql > qr)
            return;
        if (x <= t[id].Min[0])
            return;
        if (l == r) {
            x = max(x, t[id].Min[0]);
            t[id].sum = x;
            t[id].Min[0] = x;
            t[id].Min[1] = INF;
            return;
        }
        if (l >= ql && r <= qr) {
            if (x > t[id].Min[0] && x < t[id].Min[1]) {
                t[id].add(x);
                return;
            }
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
} seg;

ll gao(int l, int mid, int r) {
    seg.build(1, mid, r);
    memset(b, -1, sizeof b);
    memset(c, -1, sizeof c);
    d[r + 1] = 0;
    for (int i = 1; i < l; ++i) {
        for (auto &it : fac[a[i]]) {
            if (b[it] != -1) {
                d[r + 1] = max(d[r + 1], it);
            }
            b[it] = i;
        }
    }
    for (int i = r; i >= mid; --i) {
        d[i] = d[i + 1];
        seg.update(1, mid, r, i, i, d[i]);
        for (auto &it : fac[a[i]]) {
            if (b[it] != -1 || c[it] != -1) {
                d[i] = max(d[i], it);
            }
            if (c[it] == -1)
                c[it] = i;
        }
    }
    ll res = 0;
    for (int i = l; i <= mid; ++i) {
        res += seg.t[1].sum;
        //		dbg(i, seg.t[1].sum);
        for (auto &it : fac[a[i]]) {
            if (b[it] != -1) {
                seg.update(1, mid, r, mid, r, it);
            } else if (c[it] != -1) {
                // dbg(i, it, mid, c[it] - 1);
                seg.update(1, mid, r, mid, c[it] - 1, it);
            }
            b[it] = i;
        }
    }
    return res;
}

int main() {
    fac.clear();
    fac.resize(N);
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            fac[j].push_back(i);
        }
    }
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        if (n == 1) {
            puts("0");
            continue;
        }
        memset(b, -1, sizeof b);
        int Max = 1, x = 1, y = 2;
        for (int i = 1; i <= n; ++i) {
            for (auto &it : fac[a[i]]) {
                if (b[it] != -1) {
                    if (it > Max) {
                        Max = it;
                        x = b[it];
                        y = i;
                    }
                }
                b[it] = i;
            }
        }
        if (Max == 1) {
            printf("%lld\n", f(n) - 3);
        } else {
            res = 1ll * Max * (f(x - 1) + f(y - x - 1) + f(n - y));
            //		dbg(res);
            res += gao(1, x, n);
            //			dbg(gao(1, x, n));
            res += gao(x + 1, y, n);
            //		dbg(gao(x + 1, y, n));
            printf("%lld\n", res);
        }
    }
    return 0;
}

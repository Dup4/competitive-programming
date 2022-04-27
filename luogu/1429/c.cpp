#include <bits/stdc++.h>
#define rep(i, j, k) for (register int i = j; i <= k; i++)
#define rrep(i, j, k) for (register int i = j; i >= k; i--)
#define erep(i, u) for (register int i = head[u]; ~i; i = nxt[i])
#define print(a) printf("%lld", (ll)(a))
#define println(a) printf("%lld\n", (ll)(a))
#define printbk(a) printf("%lld ", (ll)(a))
using namespace std;
const int MAXN = 1e6 + 11;
const int INF = 0x7fffffff;
typedef long long ll;
ll read() {
    ll x = 0, f = 1;
    register char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int D;
struct point {
    int x[2];
    bool operator<(const point &rhs) const {
        return x[D] < rhs.x[D];
    }
};
struct KD {
    int son[MAXN][2];
    point p[MAXN], mn[MAXN], mx[MAXN];
    int root, ans, tot;
    void init() {
        ans = INF;
        tot = D = 0;
    }
    void pu(int o) {
        rep(i, 0, 1) {
            if (son[o][i])
                rep(j, 0, 1) {
                    if (mn[son[o][i]].x[j] < mn[o].x[j])
                        mn[o].x[j] = mn[son[o][i]].x[j];
                    if (mx[son[o][i]].x[j] > mx[o].x[j])
                        mx[o].x[j] = mx[son[o][i]].x[j];
                }
        }
    }
    int build(int now, int l, int r) {
        int mid = l + r >> 1;
        tot++;
        son[mid][0] = son[mid][1] = 0;
        D = now;
        nth_element(p + l, p + mid, p + r + 1);  //[l,r+1)
        mn[mid].x[0] = mx[mid].x[0] = p[mid].x[0];
        mn[mid].x[1] = mx[mid].x[1] = p[mid].x[1];
        if (l < mid)
            son[mid][0] = build(now ^ 1, l, mid - 1);
        if (r > mid)
            son[mid][1] = build(now ^ 1, mid + 1, r);
        pu(mid);
        return mid;
    }
    void insert(int &o, int now, point v) {
        if (!o) {
            o = ++tot;
            p[o].x[0] = mn[o].x[0] = mx[o].x[0] = v.x[0];
            p[o].x[1] = mn[o].x[1] = mx[o].x[1] = v.x[1];
        } else {
            insert(son[o][p[o].x[now] < v.x[now]], now ^ 1, v);
            pu(o);
        }
    }
    inline int dis(point &a, point &b) {
        return abs(a.x[0] - b.x[0]) + abs(a.x[1] - b.x[1]);
    }
    inline int eva(int o, point &v) {
        int res = 0;
        rep(i, 0, 1) if (v.x[i] < mn[o].x[i] || v.x[i] > mx[o].x[i]) {
            if (v.x[i] < mn[o].x[i])
                res += mn[o].x[i] - v.x[i];
            else
                res += v.x[i] - mx[o].x[i];
        }
        return res;
    }
    void query(int o, point v) {
        if (!o)
            return;
        int d1 = dis(p[o], v), d2 = INF, d3 = INF;
        if (d1 < ans)
            ans = d1;
        if (son[o][0])
            d2 = eva(son[o][0], v);
        if (son[o][1])
            d3 = eva(son[o][1], v);
        if (d2 < d3) {
            if (d2 < ans)
                query(son[o][0], v);
            if (d3 < ans)
                query(son[o][1], v);
        } else {
            if (d3 < ans)
                query(son[o][1], v);
            if (d2 < ans)
                query(son[o][0], v);
        }
    }
    inline int query(point v) {
        ans = INF;
        query(root, v);
        return ans;
    }
} kd;
int main() {
    int n, m;
    while (cin >> n >> m) {
        kd.init();
        rep(i, 1, n) {
            kd.p[i].x[0] = read();
            kd.p[i].x[1] = read();
        }
        kd.root = kd.build(0, 1, n);
        rep(i, 1, m) {
            int op = read();
            point tmp;
            tmp.x[0] = read();
            tmp.x[1] = read();
            if (op == 1) {
                kd.insert(kd.root, 0, tmp);
            } else {
                println(kd.query(tmp));
            }
        }
    }
    return 0;
}

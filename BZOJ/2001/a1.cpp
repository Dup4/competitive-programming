#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
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
typedef long long ll;
const int N = 5e4 + 10;
const int INF = 0x3f3f3f3f;
int n, m, q, eW[N];

struct Edge {
    int u, v, id;
    ll w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} e[N];

struct qNode {
    int id;
    ll val, ans;
} qrr[N];

struct UFS {
    int fa[N];
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    bool merge(int u, int v) {
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            fa[fu] = fv;
            return true;
        }
        return false;
    }
    void reset(const vector<Edge> &e) {
        for (int i = 0; i < SZ(e); ++i) fa[e[i].u] = fa[e[i].v] = 0;
    }
} ufs;

namespace CDQ {
vector<Edge> t[30], tmp, ttmp;
//删除无用边
void Reduction() {
    ufs.reset(tmp);
    sort(tmp.begin(), tmp.end());
    ttmp.clear();
    for (int i = 0, u, v; i < SZ(tmp); ++i) {
        u = tmp[i].u, v = tmp[i].v;
        if (tmp[i].w == INF || ufs.merge(u, v)) {
            ttmp.push_back(tmp[i]);
        }
    }
    tmp = ttmp;
}
//缩掉必须边
void Contraction(ll &must) {
    ufs.reset(tmp);
    sort(tmp.begin(), tmp.end());
    ttmp.clear();
    for (int i = 0, u, v; i < SZ(tmp); ++i) {
        u = tmp[i].u, v = tmp[i].v;
        if (ufs.merge(u, v)) {
            ttmp.push_back(tmp[i]);
        }
    }
    ufs.reset(ttmp);
    for (int i = 0, u, v; i < SZ(ttmp); ++i) {
        u = ttmp[i].u, v = ttmp[i].v;
        if (ttmp[i].w != -INF && ufs.merge(u, v)) {
            must += ttmp[i].w;
        }
    }
    ttmp.clear();
    for (int i = 0; i < SZ(tmp); ++i) {
        int u = ufs.find(tmp[i].u), v = ufs.find(tmp[i].v);
        if (u != v) {
            tmp[i].u = v;
            tmp[i].v = v;
            ttmp.push_back(tmp[i]);
        }
    }
    tmp = ttmp;
}
void solve(int l, int r, int dep, ll must) {
    if (l == r)
        eW[qrr[l].id] = qrr[l].val;
    for (int i = 0; i < SZ(t[dep]); ++i) {
        t[dep][i].w = eW[t[dep][i].id];
    }
    tmp = t[dep];
    if (l == r) {
        qrr[l].ans = must;
        ufs.reset(tmp);
        sort(tmp.begin(), tmp.end());
        for (int i = 0, u, v; i < SZ(tmp); ++i) {
            u = tmp[i].u, v = tmp[i].v;
            if (ufs.merge(u, v)) {
                qrr[l].ans += tmp[i].w;
            }
        }
        return;
    }
    for (int i = 0; i < SZ(tmp); ++i)
        if (tmp[i].id >= l && tmp[i].id <= r)
            tmp[i].w = INF;
    Reduction();
    for (int i = 0; i < SZ(tmp); ++i)
        if (tmp[i].id >= l && tmp[i].id <= r)
            tmp[i].w = -INF;
    Contraction(must);
    t[dep + 1] = tmp;
    int mid = (l + r) >> 1;
    solve(l, mid, dep + 1, must);
    solve(mid + 1, r, dep + 1, must);
}
void gao() {
    t[0].clear();
    for (int i = 1; i <= m; ++i) t[0].push_back(e[i]);
    solve(1, q, 0, 0);
}
}  // namespace CDQ

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; ++i) {
        e[i].id = i;
        scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
        eW[i] = e[i].w;
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%d%lld", &qrr[i].id, &qrr[i].val);
    }
    CDQ::gao();
    for (int i = 1; i <= q; ++i) printf("%lld\n", qrr[i].ans);
    return 0;
}

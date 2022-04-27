#include <bits/stdc++.h>
#define N 600010
#define INF 0x3f3f3f3f
#define eps 1e-10
// #define pi 3.141592653589793
#define P 1000000007
#define LL long long
#define pb push_back
#define fi first
#define se second
#define cl clear
#define si size
#define lb lower_bound
#define ub upper_bound
#define mem(x) memset(x, 0, sizeof x)
#define sc(x) scanf("%d", &x)
#define scc(x, y) scanf("%d%d", &x, &y)
#define sccc(x, y, z) scanf("%d%d%d", &x, &y, &z)
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pp;

map<pi, int> mp;
vector<pi> a[N << 1];
LL nx[N], ny[N], sz[N], ans[N], fa[N], res;
pi st[N];
int op = 0;
int getfa(int x) {
    return (fa[x] == x ? x : getfa(fa[x]));
}

void ins(int x, int fl, int fr, int l, int r, pi t) {
    if (l == fl && fr == r)
        a[x].pb(t);
    else {
        int mid = l + r >> 1;
        if (fr <= mid)
            ins(x << 1, fl, fr, l, mid, t);
        else if (fl > mid)
            ins(x << 1 | 1, fl, fr, mid + 1, r, t);
        else {
            ins(x << 1, fl, mid, l, mid, t);
            ins(x << 1 | 1, mid + 1, fr, mid + 1, r, t);
        }
    }
}

void spy(int x, int l, int r) {
    int tm = op;
    for (auto i : a[x]) {
        int x = getfa(i.fi), y = getfa(i.se);
        if (x != y) {
            if (sz[x] < sz[y])
                swap(x, y);
            st[++op] = pi(x, y);
            fa[y] = x;
            res -= nx[x] * ny[x] + nx[y] * ny[y];
            sz[x] += sz[y];
            nx[x] += nx[y];
            ny[x] += ny[y];
            res += nx[x] * ny[x];
        }
    }
    if (l == r)
        ans[l] = res;
    else {
        spy(x << 1, l, l + r >> 1);
        spy(x << 1 | 1, (l + r >> 1) + 1, r);
    }
    while (tm != op) {
        int x = st[op].fi, y = st[op--].se;
        res -= nx[x] * ny[x];
        sz[x] -= sz[y];
        nx[x] -= nx[y];
        ny[x] -= ny[y];
        res += nx[x] * ny[x] + nx[y] * ny[y];
        fa[y] = y;
    }
}

int main() {
    int n;
    sc(n);
    for (int i = 1, x, y; i <= n; i++) {
        scc(x, y);
        y += 3e5;
        if (mp[pi(x, y)]) {
            ins(1, mp[pi(x, y)], i - 1, 1, n, pi(x, y));
            mp.erase(pi(x, y));
        } else
            mp[pi(x, y)] = i;
    }
    for (auto i : mp) ins(1, i.se, n, 1, n, i.fi);
    for (int i = 1; i <= 6e5; i++) (i <= 3e5 ? nx : ny)[i] = sz[i] = 1, fa[i] = i;
    spy(1, 1, n);
    printf("%lld", ans[1]);
    for (int i = 2; i <= n; i++) printf(" %lld", ans[i]);
}

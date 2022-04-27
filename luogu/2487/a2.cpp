#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 10;
struct data {
    int x, y, z, f[2];
    double g[2];
    data() {
        x = y = z = f[1] = f[0] = 0;
        g[0] = g[1] = 0;
    }
} d[maxn], t[maxn];
bool operator<(data a, data b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
inline bool cmp(data x, data y) {
    return x.x < y.x;
}
struct Bit {
    int w;
    double sum;
    Bit() {
        w = 0;
        sum = 0;
    }
    inline void clear() {
        w = 0;
        sum = 0;
    }
} qu[maxn];
int sta[maxn], tot, n, haz[maxn], hay[maxn], tpz, tpy;
inline Bit ask(int x) {
    Bit res;
    while (x) {
        if (qu[x].w > res.w)
            res = qu[x];
        else if (qu[x].w == res.w)
            res.sum += qu[x].sum;
        x -= x & -x;
    }
    return res;
}
void update(int x, int w, double s) {
    while (x <= tpz) {
        if (qu[x].w < w) {
            if (qu[x].w == 0)
                sta[++tot] = x;
            qu[x].w = w;
            qu[x].sum = s;
        } else if (qu[x].w == w)
            qu[x].sum += s;
        x += x & -x;
    }
}
void solve(int l, int r, int p) {
    if (l == r) {
        if (d[l].f[p] < 1)
            d[l].f[p] = d[l].g[p] = 1;
        return;
    }
    int mid = (l + r) >> 1, st = l, ed = mid + 1;
    for (int i = l; i <= r; i++)
        if (d[i].x <= mid)
            t[st++] = d[i];
        else
            t[ed++] = d[i];
    for (int i = l; i <= r; i++) d[i] = t[i];
    solve(l, mid, p);
    sort(d + l, d + mid + 1);
    st = l;
    for (int i = mid + 1; i <= r; i++) {
        while (st <= mid && d[i].y >= d[st].y) update(d[st].z, d[st].f[p], d[st].g[p]), st++;
        Bit res = ask(d[i].z);
        if (!res.w)
            continue;
        if (res.w + 1 > d[i].f[p])
            d[i].f[p] = res.w + 1, d[i].g[p] = res.sum;
        else if (res.w + 1 == d[i].f[p])
            d[i].g[p] += res.sum;
    }
    for (int i = 1; i <= tot; i++) qu[sta[i]].clear();
    tot = 0;
    solve(mid + 1, r, p);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &d[i].y, &d[i].z), d[i].x = i, hay[i] = d[i].y, haz[i] = d[i].z;
    sort(hay + 1, hay + 1 + n);
    sort(haz + 1, haz + 1 + n);
    tpy = unique(hay + 1, hay + 1 + n) - hay - 1;
    tpz = unique(haz + 1, haz + 1 + n) - haz - 1;
    for (int i = 1; i <= n; i++)
        d[i].y = tpy - (lower_bound(hay + 1, hay + 1 + tpy, d[i].y) - hay) + 1,
        d[i].z = tpz - (lower_bound(haz + 1, haz + 1 + tpz, d[i].z) - haz) + 1;
    sort(d + 1, d + 1 + n);
    solve(1, n, 0);
    for (int i = 1; i <= n; i++) d[i].x = n - d[i].x + 1, d[i].y = tpy - d[i].y + 1, d[i].z = tpz - d[i].z + 1;
    reverse(d + 1, d + 1 + n);
    sort(d + 1, d + 1 + n);
    solve(1, n, 1);
    int ans = 0;
    double Sum;
    sort(d + 1, d + 1 + n, cmp);
    reverse(d + 1, d + 1 + n);
    for (int i = 1; i <= n; i++)
        if (ans < d[i].f[0])  //寻找最长的LIS
        {
            ans = d[i].f[0];
            Sum = d[i].g[0];
        } else if (ans == d[i].f[0])
            Sum += d[i].g[0];
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
        int len = d[i].f[0] + d[i].f[1] - 1;
        double res = 0;
        if (len == ans)
            res = d[i].g[0] * d[i].g[1] / Sum;
        printf("%.5f%c", res, " \n"[i == n]);
    }
    return 0;
}

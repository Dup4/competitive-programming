#include <bits/stdc++.h>
#define fo(i, x, y) for (int i = x, B = y; i <= B; i++)
#define ff(i, x, y) for (int i = x, B = y; i < B; i++)
#define fd(i, x, y) for (int i = x, B = y; i >= B; i--)
#define ll long long
#define ul unsigned long long
using namespace std;

const int N = 1e5 + 5;

int n, Q;
struct P {
    ll x, y;
    P(ll _x = 0, ll _y = 0) {
        x = _x, y = _y;
    }
} a[N], w;

P operator+(P a, P b) {
    return P(a.x + b.x, a.y + b.y);
}
P operator-(P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
ll operator^(P a, P b) {
    return a.x * b.y - a.y * b.x;
}
bool operator<(P a, P b) {
    return a.y == b.y ? a.x < b.x : a.y > b.y;
}

P _d[N * 20];
int us[N], z[N], z0, zm;
void build_tb(P *a, int &a0) {
    sort(a + 1, a + a0 + 1);
    fo(i, 1, a0) us[i] = 0;
    z[z0 = 1] = 1;
    fo(i, 2, a0) {
        while (z0 > 1 && ((a[z[z0]] - a[z[z0 - 1]]) ^ (a[i] - a[z[z0]])) <= 0) us[z[z0--]] = 0;
        us[z[++z0] = i] = 1;
    }
    zm = z0;
    fd(i, a0 - 1, 1) if (!us[i]) {
        while (z0 > zm && ((a[z[z0]] - a[z[z0 - 1]]) ^ (a[i] - a[z[z0]])) <= 0) us[z[z0--]] = 0;
        us[z[++z0] = i] = 1;
    }
    z0--;
    fo(i, 1, a0) _d[i] = a[i];
    a0 = 0;
    fo(i, 1, z0) a[++a0] = _d[z[i]];
}

P d[N * 20];
int d0;
P p[N], q[N];
int p0, q0;

void dg(int x, int y) {
    if (x == y) {
        d[++d0] = a[x];
        return;
    }
    int m = x + y >> 1;
    dg(x, m);
    dg(m + 1, y);
    p[p0 = 1] = a[m];
    fd(i, m - 1, x) p0++, p[p0] = p[p0 - 1] + a[i];
    q[q0 = 1] = a[m + 1];
    fo(i, m + 2, y) q0++, q[q0] = q[q0 - 1] + a[i];
    build_tb(p, p0);
    build_tb(q, q0);
    p[++p0] = p[1];
    q[++q0] = q[1];
    int l = 1, r = 1;
    P u = p[1] + q[1], v = u;
    d[++d0] = u;
    while (l < p0 && r < q0) {
        if (((p[l + 1] - p[l]) ^ (q[r + 1] - q[r])) >= 0) {
            v = u + (p[l + 1] - p[l]);
            d[++d0] = v;
            l++;
            u = v;
        } else {
            v = u + (q[r + 1] - q[r]);
            d[++d0] = v;
            r++;
            u = v;
        }
    }
    while (l < p0) {
        v = u + (p[l + 1] - p[l]);
        d[++d0] = v;
        l++;
        u = v;
    }
    while (r < q0) {
        v = u + (q[r + 1] - q[r]);
        d[++d0] = v;
        r++;
        u = v;
    }
}

#define db double

db jj(P a) {
    return atan2(a.y, a.x);
}
db jo[N * 20];

int main() {
    scanf("%d %d", &n, &Q);
    fo(i, 1, n) scanf("%lld %lld", &a[i].x, &a[i].y);
    dg(1, n);
    build_tb(d, d0);
    fo(i, 1, d0 - 1) jo[i] = jj(d[i + 1] - d[i]);
    jo[d0] = jj(d[1] - d[d0]);
    fo(ii, 1, Q) {
        scanf("%lld %lld", &w.x, &w.y);
        db wj = atan2(-w.y, -w.x);
        ll ans = max(w ^ d[1], w ^ d[d0]);
        int as = 0;
        for (int l = 1, r = d0; l <= r;) {
            int m = l + r >> 1;
            if (jo[m] <= wj)
                as = m, l = m + 1;
            else
                r = m - 1;
        }
        if (as) {
            ans = max(ans, w ^ d[as]);
            ans = max(ans, w ^ d[as + 1]);
        }
        printf("%lld\n", max(1ll * 0, ans));
    }
}

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n, q, m, lg;

struct star {
    int x, y, s, id, op;
} a[N], c[N * 5], d[N * 5], d0[N * 5];

struct rec {
    int x[2], y[2], t, d;
} b[N];

ll cnt[N], sum[N], cntl[N];

ll C[2][N];

int lb(int x) {
    return x & (-x);
}

void add(ll *C, int i, int x) {
    while (i <= n) C[i] += x, i += lb(i);
}

ll ask(ll *C, int i) {
    ll res = 0;
    while (i > 0) res += C[i], i -= lb(i);
    return res;
}

bool cmp1(const star &a, const star &b) {
    if (a.x != b.x)
        return a.x < b.x;
    if (a.y != b.y)
        return a.y < b.y;
    return a.id < b.id;
}

bool cmp2(const star &a, const star &b) {
    if (a.s != b.s)
        return a.s < b.s;
    return a.id < b.id;
}

void solve12() {
    for (int i = 1; i <= n; i++) c[i] = a[i];
    for (int i = 1, j = n; i <= q; i++) {
        c[++j] = (star){b[i].x[0] - 1, b[i].y[0] - 1, 1, i};
        c[++j] = (star){b[i].x[0] - 1, b[i].y[1], -1, i};
        c[++j] = (star){b[i].x[1], b[i].y[0] - 1, -1, i};
        c[++j] = (star){b[i].x[1], b[i].y[1], 1, i};
    }
    sort(c + 1, c + n + q * 4 + 1, cmp1);
    for (int i = 1; i <= n + q * 4; i++) {
        if (c[i].id == 0)
            add(C[0], c[i].y, 1), add(C[1], c[i].y, c[i].s);
        else
            cnt[c[i].id] += ask(C[0], c[i].y) * c[i].s, sum[c[i].id] += ask(C[1], c[i].y) * c[i].s;
    }
    for (int i = 1; i <= n; i++) C[0][i] = C[1][i] = 0;
}

void solve(int l, int r) {
    if (l >= r)
        return;
    int mid = l + r >> 1, k = 0, t = 0, i, j;
    solve(l, mid), solve(mid + 1, r);
    for (i = l, j = mid + 1; j <= r;) {
        while (i <= mid && d[i].id != 0) i++;
        while (j <= r && d[j].id == 0) j++;
        if (j > r)
            break;
        if (i > mid) {
            for (; j <= r; j++)
                if (d[j].id != 0)
                    d0[++k] = d[j];
            break;
        } else {
            if (cmp1(d[i], d[j]))
                d0[++k] = d[i++], t++;
            else
                d0[++k] = d[j++];
        }
    }
    for (i = 1; i <= k; i++)
        if (d0[i].id == 0)
            add(C[0], d0[i].y, 1);
        else
            cntl[d0[i].id] += ask(C[0], d0[i].y) * d0[i].op;
    if (t * lg > n * 4) {
        for (int i = 1; i <= n; i++) C[0][i] = 0;
    } else {
        for (i = 1; i <= k; i++)
            if (d0[i].id == 0)
                add(C[0], d0[i].y, -1);
        for (k = l - 1, i = l, j = mid + 1; i <= mid && j <= r;) {
            if (cmp1(d[i], d[j]))
                d0[++k] = d[i++];
            else
                d0[++k] = d[j++];
        }
    }
    while (i <= mid) d0[++k] = d[i++];
    while (j <= r) d0[++k] = d[j++];
    for (i = l; i <= r; i++) d[i] = d0[i];
}

void solve3() {
    for (int i = 1; i <= n; i++) d[i] = a[i];
    for (int i = 1, j = n; i <= q; i++) {
        b[i].d = m - b[i].t;
        d[++j] = (star){b[i].x[0] - 1, b[i].y[0] - 1, b[i].d, i, 1};
        d[++j] = (star){b[i].x[0] - 1, b[i].y[1], b[i].d, i, -1};
        d[++j] = (star){b[i].x[1], b[i].y[0] - 1, b[i].d, i, -1};
        d[++j] = (star){b[i].x[1], b[i].y[1], b[i].d, i, 1};
    }
    sort(d + 1, d + n + q * 4 + 1, cmp2);
    solve(1, n + q * 4);
}

#define ck(x, l, r)           \
    if ((x < l) || (x > r)) { \
        return 0;             \
    }

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q >> m, lg = log2(n + 0.5);
    ck(n, 1, 5e4);
    ck(q, 1, 5e4);
    ck(m, 1, 1e9);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].s;
        ck(a[i].x, 1, n);
        ck(a[i].y, 1, n);
        ck(a[i].s, 0, m);
    }
    for (int i = 1; i <= q; i++) {
        cin >> b[i].t >> b[i].x[0] >> b[i].y[0] >> b[i].x[1] >> b[i].y[1];
        ck(b[i].t, 0, m);
        ck(b[i].x[0], 1, n);
        ck(b[i].x[1], 1, n);
        ck(b[i].y[0], 1, n);
        ck(b[i].y[1], 1, n);
    }
    solve12(), solve3();
    for (int i = 1; i <= q; i++) cout << sum[i] + cnt[i] * b[i].t - (cnt[i] - cntl[i]) * (m + 1) << '\n';
    return 0;
}

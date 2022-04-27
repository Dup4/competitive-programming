#include <bits/stdc++.h>
using namespace std;

#define MAXN 500005
#define se set<aa>
#define it iterator
#define lowbit(x) (x & (-x))
#define int long long

int n, m, q;
struct op {
    int l, r, v;
} a[MAXN];

struct qr {
    int l, r, i;
} b[MAXN];
int ans[MAXN];

struct aa {
    int l, r, v, i;
};
set<aa> s;
int c[MAXN];

void add(int x, int y) {
    if (x == 0)
        return;
    for (; x <= n; x += lowbit(x)) c[x] += y;
}

int qsum(int x) {
    int ans = 0;
    for (; x > 0; x -= lowbit(x)) ans += c[x];
    return ans;
}

inline int read() {
    register int x = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x;
}

bool cmp(qr a, qr b) {
    return a.r < b.r;
}

bool operator<(aa a, aa b) {
    return a.r < b.r;
}

void rd() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        a[i].l = read();
        a[i].r = read();
        a[i].v = read();
    }
    for (int i = 1; i <= q; i++) {
        b[i].l = read();
        b[i].r = read();
        b[i].i = i;
    }
    sort(b + 1, b + q + 1, cmp);
    s.insert((aa){1, m, 0, 0});
}

void split(se::it i, int x) {
    int l = i->l, r = i->r, v = i->v, _i = i->i;
    if (x < l || x >= r)
        return;
    s.erase(i);
    s.insert((aa){l, x, v, _i});
    s.insert((aa){x + 1, r, v, _i});
}

void Assign(int l, int r, int v, int i) {
    se::it x = s.lower_bound((aa){0, l - 1, 0, 0});
    split(x, l - 1);
    se::it y = s.lower_bound((aa){0, r, 0, 0});
    split(y, r);

    x = s.lower_bound((aa){0, l, 0, 0});
    y = s.lower_bound((aa){0, r + 1, 0, 0});
    for (se::it i = x; i != y;) {
        se::it j = i;
        i++;
        add(j->i, -((j->r) - (j->l) + 1) * (j->v));
        s.erase(j);
    }
    s.insert((aa){l, r, v, i});
    add(i, (r - l + 1) * v);
}

signed main() {
    rd();
    for (int i = 1; i <= q; i++) {
        for (int j = b[i - 1].r + 1; j <= b[i].r; j++) {
            Assign(a[j].l, a[j].r, a[j].v, j);
        }
        ans[b[i].i] = qsum(n) - qsum(b[i].l - 1);
    }
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}
/*
4 5 3
1 4 3
2 3 1
5 5 2
1 2 4

1 2
1 4
2 3

8
14
4

*/

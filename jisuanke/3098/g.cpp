#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, q;
struct node {
    int a, b, c;
    node() {}
    node(int a, int b, int c) : a(a), b(b), c(c) {}
    bool operator<=(const node &other) const {
        return a <= other.a || b <= other.b || c <= other.c;
    }
} p[N];
pii a[N], b[N], c[N];

void Min(node &x, node y) {
    x.a = min(x.a, y.a);
    x.b = min(x.b, y.b);
    x.c = min(x.c, y.c);
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].fi);
            a[i].se = i;
            p[i].a = a[i].fi;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i].fi);
            b[i].se = i;
            p[i].b = b[i].fi;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &c[i].fi);
            c[i].se = i;
            p[i].c = c[i].fi;
        }
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);
        sort(c + 1, c + 1 + n);
        node T = node(1e9, 1e9, 1e9);
        Min(T, p[a[n].se]);
        Min(T, p[b[n].se]);
        Min(T, p[c[n].se]);
        for (int i = n - 1; i >= 1; --i) {
            int pos = a[i].se;
            if (T <= p[pos]) {
                Min(T, p[pos]);
            }
            pos = b[i].se;
            if (T <= p[pos]) {
                Min(T, p[pos]);
            }
            pos = c[i].se;
            if (T <= p[pos]) {
                Min(T, p[pos]);
            }
        }
        int x;
        while (q--) {
            scanf("%d", &x);
            puts(T <= p[x] ? "YES" : "NO");
        }
    }
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
struct {
    inline operator int() {
        int x;
        return scanf("%d", &x), x;
    }
    inline operator ll() {
        ll x;
        return scanf("%lld", &x), x;
    }
} read;

const int maxn = 100005;
int tpos[maxn], thei[maxn];
struct Two {
    int x, y, z;
} a[maxn];
int tmp[maxn];
ll bit[maxn];

ll query(int p) {
    ll res = 0;
    for (int k = p; k; k -= k & -k) res = std::max(res, bit[k]);
    return res;
}

void modify(int p, ll x) {
    for (int k = p; k < maxn; k += k & -k) bit[k] = std::max(bit[k], x);
}

int main() {
    int n = read, m = read;
    for (int i = 1; i <= m; i++) tpos[i] = read;
    for (int i = 1; i <= m; i++) thei[i] = read;

    for (int i = 1; i <= n; i++) {
        int t = read, p = read, c = read;
        int x = tpos[p];
        int y = thei[p] + t;
        a[i] = {x - y, -x - y, c};
        a[i].x *= -1;
        a[i].y *= -1;
    }

    std::sort(a + 1, a + n + 1, [](Two A, Two B) {
        return A.x == B.x ? A.y < B.y : A.x < B.x;
    });

    for (int i = 1; i <= n; i++) tmp[i] = a[i].y;
    std::sort(tmp + 1, tmp + n + 1);

    for (int i = 1; i <= n; i++) {
        int x = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i].y) - tmp);
        modify(x, query(x) + a[i].z);
    }

    printf("%lld\n", query(n));
}

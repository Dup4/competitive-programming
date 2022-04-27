#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
int n;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    ll operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }
    ll operator^(const Point &b) const {
        return x * b.y - y * b.x;
    }
    bool operator<(const Point &b) const {
        if (y * b.y <= 0) {
            if (y > 0 || b.y > 0)
                return y < b.y;
            if (y == 0 && b.y == 0)
                return x < b.x;
        }
        return x * b.y - y * b.x > 0;
    }
} p[N], q[N << 1];

ll gao() {
    ll line = 0, res = 0;
    for (int i = 0; i < n; ++i) {
        int tot = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            q[tot++] = p[j] - p[i];
        }
        int tmp = 0;
        sort(q, q + tot);
        for (int j = 0; j < tot; ++j) q[tot + j] = q[j];
        for (int j = 0; j < tot - 1; ++j) {
            if ((q[j] ^ q[j + 1]) == 0)
                ++tmp;
            else
                tmp = 0;
            line += tmp;
        }
        int cnt1 = 0, cnt2 = 0;
        for (int j = 0; j < tot; ++j) {
            //左边锐角个数
            while (cnt1 <= j || (cnt1 - tot < j && (q[cnt1] ^ (q[j])) < 0 && (q[cnt1] * q[j]) > 0)) cnt1++;
            //左边角个数
            while (cnt2 <= j || (cnt2 - tot < j && (q[cnt2] ^ q[j]) < 0)) cnt2++;
            res += cnt2 - cnt1;
        }
    }
    return res + line / 3;
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld", &p[i].x, &p[i].y);
        }
        ll ans = 1ll * n * (n - 1) * (n - 2) / 6 - gao();
        printf("%lld\n", ans);
    }
    return 0;
}

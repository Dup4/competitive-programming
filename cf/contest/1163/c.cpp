#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
#define pii pair<int, int>
#define fi first
#define se second
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int n, m, x[N], y[N];
struct node {
    int a, b, c;
    node() {}
    node(int a, int b, int x1, int y1) {
        if (a < 0 || (a == 0 && b < 0)) {
            a = -a;
            b = -b;
        }
        int g = gcd(a, b);
        a /= g;
        b /= g;
        c = 1ll * a * x1 - 1ll * b * y1;
        this->a = a;
        this->b = b;
    }
    bool operator<(const node &other) const {
        if (a != other.a) {
            return a < other.a;
        } else if (b != other.b) {
            return b < other.b;
        } else {
            return c < other.c;
        }
    }
    bool operator==(const node &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
} a[N];
map<pii, int> mp;

int main() {
    while (scanf("%d", &n) != EOF) {
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", x + i, y + i);
        }
        m = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int y1 = y[i], y2 = y[j];
                int x1 = x[i], x2 = x[j];
                a[++m] = node(y1 - y2, x1 - x2, x1, y1);
            }
        }
        sort(a + 1, a + 1 + m);
        m = unique(a + 1, a + 1 + m) - a - 1;
        //	for (int i = 1; i <= m; ++i) {
        //		printf("%d %d %d\n", a[i].a, a[i].b, a[i].c);
        //	}
        ll res = 0;
        for (int i = 1; i <= m; ++i) {
            int A = a[i].a, B = a[i].b;
            res += (i - 1) - mp[pii(A, B)];
            ++mp[pii(A, B)];
        }
        printf("%lld\n", res);
    }
    return 0;
}

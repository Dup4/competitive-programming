#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define INF 0x3f3f3f3f
int n, m;
struct node {
    int x, y;
    int f[4];
    node() {}
    void scan() {
        scanf("%d%d", &x, &y);
        for (int i = 0; i < 4; ++i) scanf("%d", f + i);
    }
} a[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) a[i].scan();
        sort(a + 1, a + 1 + n, [](node a, node b) {
            return a.x < b.x;
        });
        int D = 100000;
        int X = INF, Y = INF;
        int l = D, r = -D, pos = 1;
        bool F = 0;
        for (int i = a[1].x; i <= D; i = a[pos].x) {
            F = 1;
            while (pos <= n && a[pos].x == i) {
                if (a[pos].f[2] == 0) {
                    l = i;
                    F = 0;
                    break;
                }
                ++pos;
            }
            if (!F || pos > n)
                break;
        }
        pos = n;
        for (int i = a[n].x; i >= -D; i = a[pos].x) {
            F = 1;
            while (pos >= 1 && a[pos].x == i) {
                if (a[pos].f[0] == 0) {
                    r = i;
                    F = 0;
                    break;
                }
                --pos;
            }
            if (!F || pos < 1)
                break;
        }
        if (l >= r) {
            X = l;
        }
        sort(a + 1, a + 1 + n, [](node a, node b) {
            return a.y < b.y;
        });
        l = D, r = -D;
        pos = 1;
        for (int i = a[1].y; i <= D; i = a[pos].y) {
            F = 1;
            while (pos <= n && a[pos].y == i) {
                if (a[pos].f[1] == 0) {
                    l = i;
                    F = 0;
                    break;
                }
                ++pos;
            }
            if (!F || pos > n)
                break;
        }
        pos = n;
        for (int i = a[n].y; i >= -D; i = a[pos].y) {
            F = 1;
            while (a[pos].y == i && pos >= 1) {
                if (a[pos].f[3] == 0) {
                    r = i;
                    F = 0;
                    break;
                }
                --pos;
            }
            if (!F || pos < 1)
                break;
        }
        if (l >= r)
            Y = l;
        if (X == INF || Y == INF)
            puts("0");
        else {
            printf("%d %d %d\n", 1, X, Y);
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
    int n = 100000, m = 200000, q = 200000;
    printf("%d %d %d\n", n, m, q);
    for (int i = 2; i <= n; ++i) printf("%d %d\n", (int)(rnd() % (i - 1) + 1), i);
    for (int i = n, u, v; i <= m; ++i) {
        u = rnd() % n + 1;
        v = u;
        while (v == u) {
            v = rnd() % n + 1;
        }
        printf("%d %d\n", u, v);
    }
    for (int i = 1, u, v; i <= q; ++i) {
        u = rnd() % n + 1;
        v = u;
        while (v == u) {
            v = rnd() % n + 1;
        }
        printf("%d %d\n", u, v);
    }
    return 0;
}

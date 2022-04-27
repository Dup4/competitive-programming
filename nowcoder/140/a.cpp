#include <bits/stdc++.h>
using namespace std;

#define N 100010
const int p = 1e9 + 7;
int f[N][2], g[N];
int q, k, l, r;
void add(int &x, int y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}

int main() {
    scanf("%d%d", &q, &k);
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 0; i <= 100000; ++i) {
        add(f[i + 1][0], (f[i][0] + f[i][1]) % p);
        if (i + k <= 100000) {
            add(f[i + k][1], f[i][0]);
        }
    }
    memset(g, 0, sizeof g);
    for (int i = 1; i <= 100000; ++i) {
        g[i] = g[i - 1];
        add(g[i], f[i][0]);
        add(g[i], f[i][1]);
    }
    while (q--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", (g[r] - g[l - 1] + p) % p);
    }
    return 0;
}

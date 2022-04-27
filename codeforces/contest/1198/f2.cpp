#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, vis[N];
pii a[N];
time_t st, ed;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    mt19937 rd(time(0));
    st = time(NULL);
    ed = time(NULL);
    while (difftime(ed * 1000, st * 1000) <= 200) {
        memset(vis, 0, sizeof vis);
        shuffle(a + 1, a + 1 + n, rd);
        int x = 0, y = 0;
        int i;
        for (i = 1; i <= n; ++i) {
            if (gcd(x, a[i].fi) == x) {
                y = gcd(y, a[i].fi);
                vis[a[i].se] = 2;
            } else {
                x = gcd(x, a[i].fi);
                vis[a[i].se] = 1;
                if (x == 1)
                    break;
            }
        }
        for (++i; i <= n; ++i) {
            vis[a[i].se] = 2;
            y = gcd(y, a[i].fi);
        }
        if (y == 1) {
            puts("YES");
            for (int i = 1; i <= n; ++i) printf("%d%c", vis[i], " \n"[i == n]);
            return;
        }
        ed = time(NULL);
    }
    puts("NO");
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i].fi), a[i].se = i;
        solve();
    }
    return 0;
}

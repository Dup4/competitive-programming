#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, m;
ll a[N], b[N];
ll g;
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void work() {
    for (int i = 1; i <= m; ++i) {
        if (g % b[i] == 0) {
            puts("YES");
            printf("%lld %d\n", a[1], i);
            return;
        }
    }
    puts("NO");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%lld", b + i);
        }
        g = 0;
        for (int i = 2; i <= n; ++i) {
            g = gcd(g, a[i] - a[i - 1]);
        }
        work();
    }
    return 0;
}

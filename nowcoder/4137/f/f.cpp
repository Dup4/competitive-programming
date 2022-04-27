#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
int n, P, D, cnt[N][2];
ll A, B, C;
inline int sqr(int x) {
    return 1ll * x * x % P;
}

int main() {
    while (scanf("%d%lld%lld%lld%d%d", &n, &A, &B, &C, &P, &D) != EOF) {
        ll tot = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int f = (A * sqr(i + j) + B * sqr(i - j) + C) % P > D;
                ++cnt[i][f];
                ++cnt[j][f];
            }
            tot += 1ll * cnt[i][0] * cnt[i][1];
        }
        printf("%lld\n", 1ll * n * (n - 1) * (n - 2) / 6 - tot / 2);
    }
    return 0;
}

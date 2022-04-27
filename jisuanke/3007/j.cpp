#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
int n, x, inv[N];

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i < N; ++i) inv[i] = (inv[i - 1] + inv[i]) % mod;
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &x);
        if (x > n)
            puts("1");
        else
            printf("%d\n", (1 - (inv[n] - inv[x] + mod) % mod + mod) % mod);
    }
    return 0;
}

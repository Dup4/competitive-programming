#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
ll f[N];

int main() {
    f[1] = 1, f[2] = 6;
    int limit = 10;
    for (int i = 3; i <= limit; ++i) {
        f[i] = 2ll * f[i - 1] + 4ll * f[i - 2] + (1ll << (i - 1));
    }
    for (int n = 1; n <= limit; ++n) {
        ll res = f[n];
        for (int i = 2; i < n; ++i) {
            res += f[i - 1] * (1ll << (n - i));
            res += f[n - i] * (1ll << (i - 1));
        }
        res *= 4;
        printf("%d %lld\n", n, res);
    }
    return 0;
}

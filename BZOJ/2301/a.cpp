#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e4 + 10;
int pri[N], check[N], mu[N];
int a, b, c, d, k;
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                break;
            } else {
                mu[i * pri[j]] = -mu[i];
            }
        }
    }
    for (int i = 2; i < N; ++i) mu[i] += mu[i - 1];
}

ll calc(int l, int r) {
    l /= k;
    r /= k;
    if (l > r)
        swap(l, r);
    ll res = 0;
    for (int i = 1, j; i <= l; i = j + 1) {
        j = min(l / (l / i), r / (r / i));
        res += 1ll * (mu[j] - mu[i - 1]) * (l / i) * (r / i);
    }
    return res;
}

int main() {
    sieve();
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", calc(b, d) - calc(a - 1, d) - calc(c - 1, b) + calc(a - 1, c - 1));
    }
    return 0;
}

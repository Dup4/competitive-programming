#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e7 + 10;
ll n;
int pri[N], check[N], mu[N];
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
            } else
                mu[i * pri[j]] = -mu[i];
        }
    }
    mu[0] = 0;
    for (int i = 1; i < N; ++i) mu[i] += mu[i - 1];
}

int main() {
    sieve();
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%lld\n", &n);
        ll res = n;
        int limit = sqrt(n);
        for (int i = 2, j; i <= limit; i = j + 1) {
            ll t = n / (1ll * i * i);
            j = sqrt(n / t);
            res += t * (mu[j] - mu[i - 1]);
        }
        printf("%lld\n", res);
    }
    return 0;
}

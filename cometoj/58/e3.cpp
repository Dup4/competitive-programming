#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e6 + 10;
int pri[N], check[N], ptot;
ll phi[N];
ll n;
void init() {
    memset(check, 0, sizeof check);
    ptot = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++ptot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= ptot; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
    for (int i = 2; i < N; ++i) phi[i] += phi[i - 1];
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        ll res = 0;
        for (ll i = 1, j; i * i <= n; i = j + 1) {
            j = sqrt(n / (n / (i * i)));
            res += (n / (i * i)) * (phi[j] - phi[i - 1]);
        }
        printf("%lld\n", res);
    }
    return 0;
}

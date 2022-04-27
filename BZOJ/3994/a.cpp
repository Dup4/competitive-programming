#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int prime[N], mu[N], pred[N];
ll d[N];
bool check[N];
void init() {
    memset(check, 0, sizeof check);
    mu[1] = 1;
    prime[0] = 0;
    d[1] = 1;
    pred[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            mu[i] = -1;
            d[i] = 2;
            pred[i] = 1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                pred[i * prime[j]] = pred[i] + 1;
                d[i * prime[j]] = d[i] / (pred[i] + 1) * (pred[i] + 2);
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
                d[i * prime[j]] = d[i] * 2;
                pred[i * prime[j]] = 1;
            }
        }
    }
    for (int i = 2; i < N; ++i) mu[i] += mu[i - 1];
    for (int i = 2; i < N; ++i) d[i] += d[i - 1];
}

ll solve(int a, int b) {
    ll res = 0;
    for (int i = 1, j; i <= a; i = j + 1) {
        j = min(a / (a / i), b / (b / i));
        res += 1ll * (mu[j] - mu[i - 1]) * d[a / i] * d[b / i];
    }
    return res;
}

int main() {
    init();
    int T, n, m;
    cin >> T;
    while (T--) {
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}

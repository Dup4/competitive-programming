#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 10;
int pri[N], check[N];
ll n, mod, phi[N];

void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= *pri; ++j) {
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
    for (int i = 2; i < N; ++i) phi[i] = (phi[i - 1] + phi[i]) % mod;
}

unordered_map<int, ll> Phi;
ll get_phi(int x) {
    if (x < N)
        return phi[x];
    else
        return Phi[x];
}

void f(int x) {
    if (x < N)
        return;
    if (Phi.count(x) == 1)
        return;
    Phi[x] = (1ll * x + 1) * x / 2;
    for (int i, j = 1; j < x;) {
        i = j + 1;
        j = x / (x / i);
        f(x / i);
        Phi[x] -= 1ll * (j - i + 1) * get_phi(x / i);
    }
}

ll S2(ll n) {
    ll res = n * (n + 1) / 2;
    if (res % 3 == 0)
        return (res / 3) % mod * (n * 2 % mod + 1) % mod;
    return res % mod * ((n * 2 + 1) / 3) % mod;
}

int main() {
    while (scanf("%lld%lld", &n, &mod) != EOF) {
        sieve();
        Phi.clear();
        ll res = 0, pre = 0;
        for (int i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            f(j);
            res += 1ll * (get_phi(j) - pre + mod) % mod * S2(n / i) % mod;
            res %= mod;
            pre = get_phi(j);
        }
        printf("%lld\n", res % mod);
    }
    return 0;
}

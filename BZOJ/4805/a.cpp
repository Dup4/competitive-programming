#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
int prime[N];
ll phi[N];
bool check[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    for (int i = 2; i < N; ++i) phi[i] += phi[i - 1];
}

map<int, ll> mp;
ll f(int x) {
    if (x < N)
        return phi[x];
    if (mp.find(x) != mp.end())
        return mp[x];
    ll tot = (1ll * x * (x + 1)) / 2;
    for (int i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        tot -= 1ll * (j - i + 1) * f(x / i);
    }
    return mp[x] = tot;
}

int main() {
    mp.clear();
    init();
    int n;
    cin >> n;
    printf("%lld\n", f(n));
    return 0;
}

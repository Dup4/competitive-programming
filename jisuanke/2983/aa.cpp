#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
const ll p = 998244353;
int n, a[N], b[N];
ll inv[N];
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}
void Hash() {
    b[0] = 0;
    for (int i = 1; i <= n; ++i) {
        b[++b[0]] = a[i];
    }
    sort(b + 1, b + 1 + b[0]);
    b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + 1 + b[0], a[i]) - b;
    }
}

int main() {
    inv[0] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        inv[i] = inv[p % i] * (p - p / i) % p;
    }
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        Hash();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
struct node {
    ll a[2][2];
    node() {
        memset(a, 0, sizeof a);
    }
    node operator*(const node &other) const {
        node res = node();
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    (res.a[i][j] += a[i][k] * other.a[k][j] % p) %= p;
                }
            }
        }
        return res;
    }
} base, res;
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
void qmod(ll n) {
    while (n) {
        if (n & 1) {
            res = res * base;
        }
        base = base * base;
        n >>= 1;
    }
}

int main() {
    int n, m, k, a, b;
    while (scanf("%d%d%d%d%d", &n, &m, &k, &a, &b) != EOF) {
        a = a * qmod(b, p - 2) % p;
        b = (1 - a + p) % p;
        ll inv = qmod(n + m + 1, p - 2) * (n + m) % p;
        base = node();
        res = node();
        res.a[0][0] = n;
        res.a[0][1] = 1;
        base.a[0][0] = inv;
        base.a[1][0] = a * inv % p;
        base.a[1][1] = 1;
        qmod(k);
        printf("%lld\n", res.a[0][0]);
    }
    return 0;
}

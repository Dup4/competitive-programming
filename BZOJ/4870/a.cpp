#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 55
ll n, p;
int r, k;
struct node {
    int len;
    ll a[N][N];
    node() {}
    node(int len) {
        this->len = len;
        memset(a, 0, sizeof a);
    }
    node operator*(const node &other) const {
        node res = node(len);
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                for (int k = 0; k < len; ++k) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % p) % p;
                }
            }
        }
        return res;
    }
} base;

node qmod(node base, ll n) {
    node res = node(base.len);
    res.a[0][0] = 1, res.a[0][1] = 1;
    while (n) {
        if (n & 1) {
            res = res * base;
        }
        base = base * base;
        n >>= 1;
    }
    return res;
}
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

int main() {
    while (scanf("%lld%lld%d%d", &n, &p, &k, &r) != EOF) {
        if (k == 1) {
            printf("%lld\n", qmod(2, n));
            continue;
        }
        n *= k;
        base = node(k);
        for (int i = 1; i < k; ++i) {
            base.a[i - 1][i] = base.a[i][i] = 1;
        }
        base.a[0][0] = base.a[k - 1][0] = 1;
        printf("%lld\n", qmod(base, n - 1).a[0][r]);
    }
    return 0;
}

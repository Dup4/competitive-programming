#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 998244353;
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
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF) {
        base = node();
        res = node();
        res.a[0][0] = 0;
        res.a[0][1] = 1;
        base.a[0][0] = n - 2;
        base.a[1][0] = n - 1;
        base.a[0][1] = 1;
        qmod(k - 1);
        printf("%lld\n", res.a[0][0]);
    }
    return 0;
}

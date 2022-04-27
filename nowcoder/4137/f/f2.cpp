#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
int n, a[N][N], P, D;
ll A, B, C;
bitset<N> b[N], c[N], tb, tc, tmp, bit;

inline int sqr(int x) {
    return 1ll * x * x % P;
}

inline ll gao() {
    ll res = 0;
    int nowb = 0, nowc = 0;
    tb.reset();
    tc.reset();
    bit[n] = 1;
    for (int i = n - 1; i >= 1; --i) {
        bit[i + 1] = 1;
        tmp = (b[i] & bit) ^ tb;

        for (int j = i + 1; j <= n; ++j) {
            if (b[i][j] == 0 && tb[j] == 1) {
                tb[j] = 0;
                nowb -= (tb & b[j]).count();
            }
            if (b[i][j] == 1 && tb[j] == 0) {
                nowb += (tb & b[j]).count();
                tb[j] = 1;
            }
            if (c[i][j] == 0 && tc[j] == 1) {
                tc[j] = 0;
                nowc -= (tc & c[j]).count();
            }
            if (c[i][j] == 1 && tc[j] == 0) {
                nowc += (tc & c[j]).count();
                tc[j] = 1;
            }
        }
        res += nowb + nowc;
    }
    return res;
}

int main() {
    while (scanf("%d%lld%lld%lld%d%d", &n, &A, &B, &C, &P, &D) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                a[i][j] = (A * sqr(i + j) + B * sqr(i - j) + C) % P > D;
                if (a[i][j]) {
                    b[i][j] = b[j][i] = 1;
                } else {
                    c[i][j] = c[j][i] = 1;
                }
            }
        }
        printf("%lld\n", gao());
    }
    return 0;
}

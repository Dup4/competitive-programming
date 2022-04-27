#include <bits/stdc++.h>
using namespace std;

#define N 10000010
const int p = 1 << 30;
int prime[N];
bool check[N];
int f[N], g[N], h[N], q[N];
void init() {
    memset(check, 0, sizeof check);
    int &tot = prime[0];
    tot = 0;
    f[1] = 1;
    g[1] = 1;
    h[1] = 1;
    q[1] = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++tot] = i;
            f[i] = i;
            g[i] = i;
            q[i] = 1;
            h[i] = i - 2;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * prime[j] >= N) {
                break;
            }
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                if ((i / prime[j]) % prime[j]) {
                    h[i * prime[j]] = h[i / prime[j]] * (prime[j] - 1) * (prime[j] - 1);
                } else {
                    h[i * prime[j]] = h[i] * prime[j];
                }
                q[i * prime[j]] = q[i] + 1;
                f[i * prime[j]] = f[i];
                g[i * prime[j]] = g[i];
                int x = q[i * prime[j]];
                if (x + 1 > 2 && (x + 1) % 2 == 0) {
                    f[i * prime[j]] *= prime[j];
                }
                if (x + 2 > 3 && (x + 2) % 3 == 0) {
                    g[i * prime[j]] *= prime[j];
                }
                break;
            } else {
                f[i * prime[j]] = f[i] * f[prime[j]];
                g[i * prime[j]] = g[i] * g[prime[j]];
                h[i * prime[j]] = h[i] * h[prime[j]];
                q[i * prime[j]] = 1;
            }
        }
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        int res = 0;
        for (int i = 1; i <= A; ++i) {
            res += (A / i) * (B / f[i]) * (C / g[i]) * h[i];
        }
        printf("%d\n", (res % p + p) % p);
    }
    return 0;
}

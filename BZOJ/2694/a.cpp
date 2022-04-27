#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 4000010
const ll p = 1 << 30;
int mu[N], prime[N];
int f[N];
bool check[N];
void init() {
    memset(check, 0, sizeof check);
    prime[0] = 0;
    mu[1] = 1;
    f[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++prime[0]] = i;
            mu[i] = -1;
            f[i] = i - 1ll * i * i;
        }
        for (int j = 1; j <= prime[0]; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                if ((i / prime[j]) % prime[j])
                    f[i * prime[j]] = f[i / prime[j]] * -prime[j] * prime[j] * prime[j];
                else
                    f[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
                f[i * prime[j]] = f[i] * f[prime[j]];
            }
        }
    }
    for (int i = 2; i < N; ++i) f[i] += f[i - 1];
}

int get(int x) {
    return x * (x + 1) / 2;
}

int work(int a, int b) {
    if (a > b)
        swap(a, b);
    int res = 0;
    for (int i = 1, j; i <= a; i = j + 1) {
        j = min(a / (a / i), b / (b / i));
        res += get(a / i) * get(b / i) * (f[j] - f[i - 1]);
    }
    return res;
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%lld\n", (work(n, m) % p + p) % p);
    }
    return 0;
}

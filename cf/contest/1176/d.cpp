#include <bits/stdc++.h>
using namespace std;

#define N 400010
#define M 3000010
int prime[M], check[M], f[N], tot;
void init() {
    memset(check, 0, sizeof check);
    tot = 0;
    for (int i = 2; i < M; ++i) {
        if (!check[i]) {
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * prime[j] >= M)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    memset(check, 0, sizeof check);
    for (int i = 1; i <= tot; ++i) {
        check[prime[i]] = i;
    }
    for (int i = 2; i <= 200000; ++i) {
        for (int j = i + i; j <= 200000; j += i) {
            f[j] = i;
        }
    }
}
int n, b[N], c[M];

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        memset(c, 0, sizeof c);
        for (int i = 1; i <= 2 * n; ++i) {
            scanf("%d", b + i);
            ++c[b[i]];
        }
        vector<int> vec;
        for (int i = 2750131; i >= 2; --i)
            if (c[i]) {
                if (check[i]) {
                    c[check[i]] -= c[i];
                    while (c[i]--) {
                        vec.push_back(check[i]);
                    }
                } else {
                    c[f[i]] -= c[i];
                    while (c[i]--) {
                        vec.push_back(i);
                    }
                }
            }
        for (int i = 0; i < n; ++i) {
            printf("%d%c", vec[i], " \n"[i == n - 1]);
        }
    }
    return 0;
}

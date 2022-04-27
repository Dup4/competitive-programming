#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n, a[N], nx[N];
int prime[N], tot, check[N];
vector<vector<int>> vec;
void init() {
    memset(check, 0, sizeof check);
    tot = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * prime[j] >= N)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    vec.clear();
    vec.resize(N);
    for (int i = 1; i <= tot; ++i) {
        for (int j = prime[i]; j < N; j += prime[i]) {
            vec[j].push_back(prime[i]);
        }
    }
}

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= 1000000; ++i) {
            nx[i] = n + 1;
        }
        ll res = 0, base = 0;
        for (int i = n; i >= 1; --i) {
            for (auto it : vec[a[i]]) {
                base += (nx[it] - i);
                nx[it] = i;
            }
            res += base;
        }
        printf("%lld\n", res);
    }
    return 0;
}

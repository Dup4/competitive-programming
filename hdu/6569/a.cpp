#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define M 10010
int n, a[M], cnt[M];
vector<vector<int>> vec, fac;
int prime[M], check[M], mu[M], tot;

void init() {
    tot = 0;
    memset(check, 0, sizeof check);
    mu[1] = 1;
    fac.clear();
    fac.resize(M);
    for (int i = 2; i < M; ++i) {
        if (!check[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= tot; ++j) {
            if (1ll * i * prime[j] >= M)
                break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i < M; ++i) {
        for (int j = i; j < M; j += i) {
            fac[j].push_back(i);
        }
    }
}

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        vec.clear();
        vec.resize(M);
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            ++cnt[a[i]];
            for (auto it : fac[a[i]]) {
                vec[it].push_back(a[i]);
            }
        }
        ll res = 0;
        for (int i = 1; i < M; ++i) {
            if (vec[i].empty() || mu[i] == 0)
                continue;
            ll tmp = 0;
            sort(vec[i].begin(), vec[i].end());
            vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
            int sze = vec[i].size();
            for (auto it : vec[i]) {  //枚举上边
                int l = 0, r = 0;
                while (l < sze && vec[i][l] < it + 1) ++l;
                for (auto it2 : vec[i]) {  //枚举腰
                    if (it != it2 && cnt[it2] >= 2) {
                        while (r < sze - 1 && vec[i][r + 1] < it + 2 * it2) ++r;
                        if (l < sze && r < sze && l <= r) {
                            tmp += r - l + 1;
                            if (vec[i][l] <= it2 && it2 <= vec[i][r]) {
                                if (cnt[it2] < 3)
                                    --tmp;
                            }
                        }
                    } else if (it == it2 && cnt[it] >= 3) {
                        while (r < sze - 1 && vec[i][r + 1] < it + 2 * it2) ++r;
                        if (l < sze && r < sze && l <= r) {
                            tmp += r - l + 1;
                        }
                    }
                }
            }
            res += tmp * mu[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}

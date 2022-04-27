#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, m;
vector<vector<int> > vec;
int p[N], a[20];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        vec.clear();
        vec.resize(n + 1);
        for (int i = 1, k; i <= m; ++i) {
            scanf("%d", &k);
            for (int j = 1, x; j <= k; ++j) {
                scanf("%d", &x);
                vec[x].push_back(i);
            }
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", p + i);
        }
        int res = 0;
        for (int i = 0; i < (1 << n); ++i) {
            memset(a, 0, sizeof a);
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    for (auto it : vec[j + 1]) {
                        a[it] ^= 1;
                    }
                }
            }
            bool F = 1;
            for (int i = 1; i <= m; ++i) {
                if ((p[i] ^ a[i]) == 1) {
                    F = 0;
                    break;
                }
            }
            res += F;
        }
        printf("%d\n", res);
    }
    return 0;
}

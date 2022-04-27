#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, m, k;
set<int> se[N];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        for (int i = 1; i <= m; ++i) se[i].clear();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1, x; j <= m; ++j) {
                scanf("%d", &x);
                se[x].insert(j);
            }
        }
        for (int i = 1; i <= k; ++i) printf("%d%c", se[i].size(), " \n"[i == k]);
    }
    return 0;
}

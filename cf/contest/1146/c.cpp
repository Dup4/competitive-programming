#include <bits/stdc++.h>
using namespace std;

#define N 110
int n;

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &n);
        int res = 0;
        for (int i = 0; i < 9; ++i) {
            vector<int> a, b;
            for (int j = 1; j <= n; ++j) {
                if ((j >> i) & 1) {
                    a.push_back(j);
                } else {
                    b.push_back(j);
                }
            }
            int k1 = (int)a.size(), k2 = (int)b.size();
            if (k1 == 0 || k2 == 0) {
                continue;
            }
            printf("%d %d", k1, k2);
            fflush(stdout);
            for (auto it : a) {
                printf(" %d", it);
                fflush(stdout);
            }
            for (auto it : b) {
                printf(" %d", it);
                fflush(stdout);
            }
            printf("\n");
            fflush(stdout);
            int x;
            scanf("%d", &x);
            res = max(res, x);
        }
        printf("-1 %d\n", res);
        fflush(stdout);
    }
    return 0;
}

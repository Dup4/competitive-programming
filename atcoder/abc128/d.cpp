#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, k, a[N];

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int res = -1e9;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n + 1; ++j) {
                vector<int> vec;
                for (int k = 1; k < i; ++k) {
                    vec.push_back(a[k]);
                }
                for (int k = j; k <= n; ++k) {
                    vec.push_back(a[k]);
                }
                int sze = (int)vec.size();
                if (sze > k) {
                    continue;
                }
                sort(vec.begin(), vec.end());
                int tmp = accumulate(vec.begin(), vec.end(), 0);
                int remind = k - sze;
                for (auto it : vec) {
                    if (it < 0 && remind) {
                        tmp -= it;
                        --remind;
                    }
                }
                res = max(res, tmp);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

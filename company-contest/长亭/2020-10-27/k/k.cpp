#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, k;
int a[N], b[N], c[N];

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= k; ++i) scanf("%d", b + i), c[i] = i;
        for (int i = k + 1; i <= n; ++i) b[i] = -1, c[i] = i;
        k = max(k, n);
        int res = 0;
        do {
            int now = 0;
            for (int i = 1; i <= min(n, k); ++i) {
                if (b[c[i]] >= a[i])
                    ++now;
                // cout << c[i] << " \n"[i == min(n, k)];
            }
            res = max(res, now);
        } while (next_permutation(c + 1, c + 1 + k));
        printf("%d\n", res);
    }
    return 0;
}
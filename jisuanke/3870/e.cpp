#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        m++;
        while (q--) {
            int k;
            scanf("%d", &k);
            int t = m - 1, x = k - 1, y = n - k, ans = 0;
            while (1) {
                int p = (t + x) / m;
                ans += p;
                t = (t + x) % m;
                x -= p;
                if (t == m - 1) {
                    ++ans;
                    break;
                } else
                    t++;
                p = (y + t) / m;
                ans += p;
                t = (t + y) % m;
                y -= p;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}

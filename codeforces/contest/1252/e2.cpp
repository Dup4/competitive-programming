#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, L, R, K, a[N], l[N], r[N];

void gao() {
    l[n] = L, r[n] = R;
    for (int i = n - 1; i >= 1; --i) {
        if (a[i] == a[i + 1]) {
            l[i] = l[i + 1];
            r[i] = r[i + 1];
        } else if (a[i] < a[i + 1]) {
            r[i] = r[i + 1] - 1;
            l[i] = max(L, l[i + 1] - K);
        } else if (a[i] > a[i + 1]) {
            l[i] = l[i + 1] + 1;
            r[i] = min(R, r[i + 1] + K);
        }
        if (l[i] > r[i]) {
            puts("-1");
            return;
        }
    }
    int x = l[1];
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", x, " \n"[i == n]);
        if (i < n) {
            if (a[i] < a[i + 1]) {
                x = max(l[i + 1], x + 1);
            } else if (a[i] > a[i + 1]) {
                x = max(x - K, l[i + 1]);
            }
        }
    }
}

int main() {
    while (scanf("%d%d%d%d", &n, &L, &R, &K) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        gao();
    }
    return 0;
}

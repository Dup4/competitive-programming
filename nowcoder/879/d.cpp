#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k, a[N];

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        printf("%d\n", a[k]);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 220010
const int p = 1e9 + 7;
int f[240010];
int n, a[N];

void add(int &x, int y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            for (int j = a[i]; j < 233334; j = (j + 1) | a[i]) {
                add(f[a[i]], f[j]);
            }
            add(res, f[a[i]]);
            add(f[a[i]], 1);
        }
        printf("%d\n", res);
    }
    return 0;
}

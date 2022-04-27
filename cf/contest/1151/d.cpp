#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, arr[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        ll res = 0;
        for (int i = 1, a, b; i <= n; ++i) {
            scanf("%d%d", &a, &b);
            res += -a + 1ll * b * n;
            arr[i] = a - b;
        }
        sort(arr + 1, arr + 1 + n, [](int x, int y) {
            return x > y;
        });
        for (int i = 1; i <= n; ++i) {
            res += 1ll * i * arr[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}

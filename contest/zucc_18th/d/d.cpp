#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int a[N], _a[N], b[N], _b[N], c[N];

int main() {
    int n; 
    scanf("%d", &n);
    memset(c, 0, sizeof c);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i), _b[b[i]] = i;
    for (int i = 1; i <= n; ++i) {
        if (i >= _b[a[i]]) {
            ++c[i - _b[a[i]]];
        }
    }
    int res = n;
    for (int i = 0; i < n; ++i) {
        res = min(res, n - c[i]);
    }
    printf("%d\n", res);
    return 0;
}

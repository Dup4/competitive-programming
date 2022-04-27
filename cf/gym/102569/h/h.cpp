#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, d[N];

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        ++d[u], ++d[v];
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) res += (d[i] == 1);
    printf("%d\n", (res + 1) / 2);
    return 0;
}

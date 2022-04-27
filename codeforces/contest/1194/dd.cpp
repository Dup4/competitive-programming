#include <bits/stdc++.h>
using namespace std;

int n, k;
int f[110];

int DFS(int u) {
    if (f[u] != -1)
        return f[u];
    int res = 1;
    if (u - 1 == 0)
        return f[u] = 1;
    if (u - 2 == 0)
        return f[u] = 1;
    if (u - k == 0)
        return f[u] = 1;
    if (u - 1 > 0)
        res &= DFS(u - 1);
    if (u - 2 > 0)
        res &= DFS(u - 2);
    if (u - k > 0)
        res &= DFS(u - k);
    return f[u] = res ^ 1;
}

int main() {
    memset(f, -1, sizeof f);
    scanf("%d%d", &n, &k);
    f[1] = 1;
    f[2] = 1;
    for (int i = 1; i <= 100; ++i) printf("%d\n", DFS(i));
    return 0;
}

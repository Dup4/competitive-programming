#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 10;
int n, f[N];
char s[N];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        if (s[i] == 'E')
            f[i] += 1;
        else
            f[i] -= 1;
    }
    int Min = 0;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = max(res, f[i] - Min);
        Min = min(Min, f[i]);
    }
    printf("%d\n", res);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
vector<int> vec;
int n, a[N], f[N], ans[N];
void gao() {
    for (int i = 1; i <= n; ++i) f[i] = -2e9;
    for (int i = 1; i <= n; ++i) {
        for (auto &it : vec) {
            int nx = i + (it - 1) * (it - 1) + 1;
            if (nx > n)
                break;
            f[nx] = max(f[nx], a[i] + it);
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = max(f[i], f[i - 1]);
        ans[i] = max(ans[i], f[i] - a[i]);
    }
}

int main() {
    for (int i = 1;; ++i) {
        if (1ll * (i - 1) * (i - 1) > N)
            break;
        vec.push_back(i);
    }
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        memset(ans, 0, sizeof ans);
        gao();
        reverse(a + 1, a + 1 + n);
        reverse(ans + 1, ans + 1 + n);
        gao();
        for (int i = n; i >= 1; --i) printf("%d\n", ans[i]);
    }
    return 0;
}

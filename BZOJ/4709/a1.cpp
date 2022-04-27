#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, M = 1e4 + 10;
int n, a[N], S[N], cnt[M];
ll f[N];

namespace DP {
vector<int> sta[M];
ll calc(int x, int y) {
    return f[x - 1] + 1ll * a[x] * y * y;
}
// x < y 表示需要多少步 x这个决策点就能够比y这个决策点优
int better(int x, int y) {
    int l = 1, r = n, res = r + 1;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(x, mid - S[x] + 1) >= calc(y, mid - S[y] + 1)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res;
}
void gao() {
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        while (SZ(sta[x]) >= 2 && better(sta[x].end()[-2], sta[x].end()[-1]) <= better(sta[x].end()[-1], i))
            sta[x].pop_back();
        sta[x].push_back(i);
        while (SZ(sta[x]) >= 2 && better(sta[x].end()[-2], sta[x].end()[-1]) <= S[i]) sta[x].pop_back();
        f[i] = calc(sta[x].end()[-1], S[i] - S[sta[x].end()[-1]] + 1);
    }
    printf("%lld\n", f[n]);
}
}  // namespace DP

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = ++cnt[a[i]];
    DP::gao();
    return 0;
}

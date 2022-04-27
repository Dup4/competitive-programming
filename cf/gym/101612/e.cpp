#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, a[N];
int vis[1000010];
int fvis[1000010];
int cnt[1000010];
int ans[N][2];
vector<int> vec;
int p[1000010], q[1000010];

void File() {
    freopen("equal.in", "r", stdin);
    freopen("equal.out", "w", stdout);
}
int main() {
    File();
    while (scanf("%d", &n) != EOF) {
        memset(vis, 0, sizeof vis);
        memset(fvis, 0, sizeof fvis);
        memset(cnt, 0, sizeof cnt);
        memset(p, 0, sizeof p);
        memset(q, 0, sizeof q);
        memset(ans, 0x3f, sizeof ans);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            vis[a[i]] = 1;
            ++cnt[a[i]];
        }
        for (int i = 1; i <= 1000000; ++i) {
            for (int j = 2 * i; j <= 1000000; j += i) {
                if (vis[j]) {
                    fvis[i] = 1;
                    break;
                }
            }
        }
        for (int i = 1; i <= 1000000; ++i) {
            if (cnt[i]) {
                vec.push_back(cnt[i]);
            }
        }
        sort(vec.begin(), vec.end());
        int sze = vec.size();
        int tot = 0;
        for (auto it : vec) {
            tot += it;
            if (tot > it) {
                p[tot] = 1;
            }
        }
        vec.clear();
        for (int i = 1; i <= 1000000; ++i) {
            if (cnt[i] && fvis[i]) {
                vec.push_back(cnt[i]);
            }
        }
        sort(vec.begin(), vec.end());
        tot = 0;
        for (auto it : vec) {
            tot += it;
            q[tot] = 1;
        }
        ans[0][0] = ans[0][1] = sze;
        tot = sze;
        for (int i = 1; i <= n; ++i) {
            if (p[i]) {
                --tot;
            }
            ans[i][0] = tot;
        }
        tot = sze;
        for (int i = 1; i <= n; ++i) {
            if (q[i]) {
                --tot;
            }
            ans[i][1] = tot;
        }
        for (int i = 0; i <= n; ++i) {
            printf("%d%c", min(ans[i][0], ans[i][1]), " \n"[i == n]);
        }
    }
    return 0;
}

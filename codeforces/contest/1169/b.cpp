#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
int a[N], b[N];
map<pii, int> mp;
pii cnt[N];
bool ok() {
    for (int i = 1; i <= m; ++i) {
        if (cnt[a[i]].fi + cnt[b[i]].fi - mp[pii(a[i], b[i])] == m) {
            return true;
        }
    }
    sort(cnt + 1, cnt + 1 + n);
    for (int i = 2; i <= n; ++i) {
        for (int j = i - 1; j >= 1; --j) {
            int x = cnt[i].se, y = cnt[j].se;
            if (x > y)
                swap(x, y);
            if (mp.find(pii(x, y)) != mp.end()) {
                continue;
            } else {
                if (cnt[i].fi + cnt[j].fi == m) {
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            cnt[i] = pii(0, i);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", a + i, b + i);
            if (a[i] > b[i]) {
                swap(a[i], b[i]);
            }
            ++cnt[a[i]].fi;
            ++cnt[b[i]].fi;
            ++mp[pii(a[i], b[i])];
        }
        puts(ok() ? "YES" : "NO");
    }
    return 0;
}

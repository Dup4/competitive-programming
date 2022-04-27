#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, a[N];
int res[N];
map<int, vector<int>> mp;
map<int, int> vis;
bool F;
void merge(vector<int> &tmp, int x) {
    if (vis[x] == 0) {
        mp[x] = tmp;
        tmp.clear();
        vis[x] = 1;
    } else {
        if (x == 1) {
            for (auto it : mp[x]) res[it] = 1;
            puts("YES");
            for (int i = 1; i <= n; ++i) printf("%d", res[i]);
            puts("");
            F = 1;
            return;
        }
        for (auto it : tmp) mp[x].push_back(it);
        vis[x] = 0;
        tmp.clear();
        merge(mp[x], x - 1);
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        vector<int> tmp;
        tmp.push_back(i);
        merge(tmp, a[i]);
        if (F)
            return;
    }
    puts("NO");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        mp.clear();
        vis.clear();
        printf("Case %d: ", kase);
        scanf("%d", &n);
        F = 0;
        for (int i = 1; i <= n; ++i) res[i] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        solve();
    }
    return 0;
}

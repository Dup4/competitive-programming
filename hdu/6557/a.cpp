#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair<int, int>
#define fi first
#define se second
int n, a[N];
int res[N];
int vis[N];
vector<vector<int>> vec;
vector<int> used;
bool F;
void merge(vector<int> &tmp, int x) {
    if (!vis[x]) {
        vec[x] = tmp;
        tmp.clear();
        vis[x] = 1;
        used.push_back(x);
    } else {
        if (x == 1) {
            for (auto it : vec[1]) res[it] = 1;
            puts("YES");
            for (int i = 1; i <= n; ++i) printf("%d", res[i]);
            puts("");
            F = 1;
            return;
        }
        vis[x] = 0;
        for (auto it : tmp) vec[x].push_back(it);
        tmp.clear();
        merge(vec[x], x - 1);
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        if (a[i] < N) {
            vector<int> tmp;
            tmp.push_back(i);
            merge(tmp, a[i]);
        }
        if (F)
            return;
    }
    puts("NO");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case %d: ", kase);
        scanf("%d", &n);
        vec.clear();
        vec.resize(N);
        used.clear();
        F = 0;
        for (int i = 1; i <= n; ++i) res[i] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        solve();
        for (auto it : used) vis[it] = 0;
    }
    return 0;
}

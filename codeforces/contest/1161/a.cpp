#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m, a[N], b[N];
vector<vector<int> > vec;

bool ok(int x, int y) {
    if (b[x] == 0 || b[y] == 0) {
        return true;
    }
    if (*vec[x].begin() > vec[y].back()) {
        return true;
    }
    return false;
}

void init() {
    vec.clear();
    vec.resize(n + 1);
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        memset(b, 0, sizeof b);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", a + i);
            b[a[i]] = 1;
            vec[a[i]].push_back(i);
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (b[i] == 0) {
                ++res;
            }
            if (i > 1) {
                if (ok(i, i - 1)) {
                    ++res;
                }
            }
            if (i < n) {
                if (ok(i, i + 1)) {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

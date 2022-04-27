#include <bits/stdc++.h>
using namespace std;

#define N 2000010
int n, m, a[N], b[N], used[N], last[N];
vector<int> res;
stack<int> sta;

int main() {
    while (scanf("%d", &n) != EOF) {
        m = n * (n + 1);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", a + i);
            b[i] = i;
        }
        sort(b + 1, b + 1 + m, [&](int x, int y) {
            return a[x] < a[y];
        });
        for (int i = 1; i <= m; ++i) a[b[i]] = i;
        res.clear();
        while (!sta.empty()) sta.pop();
        memset(used, 0, sizeof used);
        memset(last, -1, sizeof last);
        for (int i = 1; i <= m; ++i) {
            int x = a[i], g = x / n;
            if (used[g])
                continue;
            if (last[g] == -1) {
                last[g] = i;
                sta.push(g);
            } else {
                res.push_back(last[g]);
                res.push_back(i);
                used[g] = 1;
                while (!sta.empty()) {
                    last[sta.top()] = -1;
                    sta.pop();
                }
            }
        }
        for (int i = 0; i < 2 * n; ++i) printf("%d%c", res[i], " \n"[i == 2 * n - 1]);
    }
    return 0;
}

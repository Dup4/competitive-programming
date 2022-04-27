#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, a[N], f[N], g[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        int res = 0;
        multiset<int> se;
        for (int i = 1; i <= n; ++i) {
            if (se.empty())
                se.insert(a[i]);
            else {
                auto pos = se.upper_bound(a[i]);
                if (pos != se.end()) {
                    ++f[i];
                    se.erase(pos);
                }
                se.insert(a[i]);
            }
        }
        res = se.size();
        se.clear();
        for (int i = n; i >= 1; --i) {
            if (se.empty())
                se.insert(a[i]);
            else {
                auto pos = se.lower_bound(a[i]);
                if (pos != se.begin()) {
                    --pos;
                    ++f[i];
                    se.erase(pos);
                }
                se.insert(a[i]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            g[i] = res;
            if (f[i] == 0)
                --g[i];
        }
        map<int, int> mp;
        for (int i = 1; i <= n; ++i) {
            if (mp.count(a[i])) {
                g[i] = min(g[i], g[mp[a[i]]]);
            }
            mp[a[i]] = i;
        }
        mp.clear();
        for (int i = n; i >= 1; --i) {
            if (mp.count(a[i])) {
                g[i] = min(g[i], g[mp[a[i]]]);
            }
            mp[a[i]] = i;
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", g[i], " \n"[i == n]);
        }
    }
    return 0;
}

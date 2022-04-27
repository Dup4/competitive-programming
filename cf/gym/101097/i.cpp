#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
int n, m;
vector<vector<int>> vec;
pii a[N];
int Max[55];

void solve() {
    sort(a + 1, a + 1 + m);
    memset(Max, 0, sizeof Max);
    set<int> se[55];
    for (int i = 1; i <= m; ++i) {
        se[a[i].se].insert(a[i].fi);
    }
    for (int i = 1; i <= m; ++i) {
        se[a[i].se].erase(a[i].fi);
        vector<pii> b;
        for (int j = 1; j <= n; ++j) {
            if (!se[j].empty()) {
                b.push_back(pii(*se[j].begin(), j));
            }
        }
        sort(b.begin(), b.end(), [](pii x, pii y) {
            return x.fi < y.fi;
        });
        for (int j = 1; j <= n; ++j)
            if (j != a[i].se) {
                int x, y, z;
                y = a[i].fi;
                if (Max[j] != 0) {
                    x = Max[j];
                    for (auto &it : b) {
                        if (it.se != a[i].se && it.se != j) {
                            z = it.fi;
                            if (x + y > z) {
                                cout << a[i].se << " " << a[i].fi << " " << j << " " << x << " " << it.se << " "
                                     << it.fi << "\n";
                                return;
                            }
                            break;
                        }
                    }
                }
            }
        Max[a[i].se] = max(Max[a[i].se], a[i].fi);
    }
    cout << "NIE\n";
}

int main() {
    freopen("sticks.in", "r", stdin);
    freopen("sticks.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) {
        m = 0;
        vec.clear();
        vec.resize(n + 1);
        for (int i = 1, num; i <= n; ++i) {
            cin >> num;
            vec[i].resize(num);
            for (auto &it : vec[i]) cin >> it;
            sort(vec[i].begin(), vec[i].end());
            vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
            for (auto &it : vec[i]) {
                a[++m] = pii(it, i);
            }
        }
        solve();
    }
    return 0;
}

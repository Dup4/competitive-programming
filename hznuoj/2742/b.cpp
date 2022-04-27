#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
int main() {
    int n, m, x, y, K, O;
    cin >> n;
    string s;
    set<string> se, All;
    for (int i = 1; i <= n; ++i) {
        cin >> m;
        set<string> tmp(se);
        for (int j = 1; j <= m; ++j) {
            cin >> s >> x >> y;
            if (j == 1)
                K = x + y;
            else {
                O = x + y;
                if (All.find(s) == All.end()) {
                    if (O < K)
                        tmp.insert(s);
                } else {
                    if (O >= K)
                        tmp.erase(s);
                }
            }
            All.insert(s);
        }
        se = tmp;
    }
    cout << se.size() << endl;
    return 0;
}

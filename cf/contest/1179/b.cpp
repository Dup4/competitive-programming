#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
int n, m;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        vector<pii> res;
        int mid = n / 2;
        for (int i = 1; i <= mid; ++i) {
            for (int j = 1; j <= m; ++j) {
                res.push_back(pii(i, j));
                res.push_back(pii(n - i + 1, m - j + 1));
            }
        }
        if (n & 1) {
            int mmid = m / 2;
            for (int j = 1; j <= mmid; ++j) {
                res.push_back(pii(mid + 1, j));
                res.push_back(pii(mid + 1, m - j + 1));
            }
            if (m & 1) {
                res.push_back(pii(mid + 1, mmid + 1));
            }
        }
        for (auto it : res) {
            printf("%d %d\n", it.fi, it.se);
        }
        //	map <pii, int> mp, mp2;
        //	for (int i = 1, sze = (int)res.size(); i < sze; ++i) {
        //		pii t = pii(res[i].fi - res[i - 1].fi, res[i].se - res[i - 1].se);
        //		pii t2 = pii(res[i].fi, res[i].se);
        //		if (mp.find(t) != mp.end() || mp2.find(t2) != mp2.end()) {
        //			cout << "no\n";
        //			break;
        //		}
        //		mp[t] = 1;
        //		mp2[t2] = 1;
        //	}
    }
    return 0;
}

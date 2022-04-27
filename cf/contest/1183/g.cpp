#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair<int, int>
#define fi first
#define se second
int n;
pii a[N];
map<int, pii> mp;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].fi, &a[i].se);
            ++mp[a[i].fi].fi;
            mp[a[i].fi].se += a[i].se;
        }
        vector<pii> vec;
        for (auto it : mp) {
            vec.push_back(it.se);
        }
        sort(vec.begin(), vec.end(), [&](pii x, pii y) {
            return x.fi > y.fi;
        });
        int pos = 0, sze = (int)vec.size();
        int a = 0, b = 0;
        priority_queue<int, vector<int>, less<int> > pq;
        for (int i = n; i >= 1; --i) {
            while (pos < sze && vec[pos].fi == i) {
                pq.push(vec[pos].se);
                ++pos;
            }
            if (!pq.empty()) {
                a += i;
                b += min(i, pq.top());
                pq.pop();
            }
        }
        printf("%d %d\n", a, b);
    }
    return 0;
}

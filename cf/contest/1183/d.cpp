#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define se second
int n, a[N];

map<int, int> mp;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            ++mp[a[i]];
        }
        vector<int> vec;
        for (auto it : mp) {
            vec.push_back(it.se);
        }
        sort(vec.begin(), vec.end(), [&](int x, int y) {
            return x < y;
        });
        priority_queue<int, vector<int>, less<int> > pq;
        int res = 0, pos = 0, sze = (int)vec.size();
        for (int i = 1; i <= n; ++i) {
            pq.push(i);
            while (pos < sze && vec[pos] == i) {
                if (!pq.empty()) {
                    res += pq.top();
                    pq.pop();
                }
                ++pos;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

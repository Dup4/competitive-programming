#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];
multiset<int> se;

bool ok() {
    int sze = se.size();
    if (sze <= 1) {
        return true;
    } else {
        int Max = *se.rbegin();
        int Min = *se.begin();
        if (Min == Max && Min == 1) {
            return true;
        }
        if (Min == Max - 1) {
            auto pos = se.end();
            --pos;
            --pos;
            if (*pos == Min) {
                return true;
            }
        }
        if (Min == 1) {
            auto pos = se.begin();
            ++pos;
            if (*pos == Max) {
                return true;
            }
        }
        return false;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof a);
        se.clear();
        int res = 0;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            if (a[x] > 0) {
                se.erase(se.lower_bound(a[x]));
            }
            ++a[x];
            se.insert(a[x]);
            if (ok()) {
                res = i;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

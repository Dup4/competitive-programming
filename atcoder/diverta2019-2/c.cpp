#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n;
vector<int> a, b;

int main() {
    while (scanf("%d", &n) != EOF) {
        a.clear();
        b.clear();
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            if (x <= 0) {
                a.push_back(x);
            } else {
                b.push_back(x);
            }
        }
        vector<pii> vec;
        sort(b.begin(), b.end());
        int base;
        for (int sze = (int)b.size(), i = 0, j = sze - 1; i <= j; ++i, --j) {
            if (i == j) {
                base = b[i];
            } else if (i + 1 == j) {
                vec.push_back(pii(b[j], b[i]));
                base = b[j] - b[i];
            } else {
                vec.push_back(pii(b[i], b[j]));
                a.push_back(b[i] - b[j]);
            }
        }
        for (auto it : a) {
            vec.push_back(pii(base, it));
            base -= it;
        }
        int sze = (int)vec.size();
        for (int i = 0; i < sze; ++i) {
            printf("%d %d\n", vec[i].fi, vec[i].se);
        }
    }
    return 0;
}

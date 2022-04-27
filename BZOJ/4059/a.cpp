#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int _T, n, a[N];
int pre[N], nx[N];
map<int, int> mp;

bool ok(int l, int r) {
    if (l > r)
        return 1;
    int L = l, R = r;
    int p = 1;
    while (L <= R) {
        if (p & 1) {
            if (pre[L] < l && nx[L] > r) {
                return ok(l, L - 1) && ok(L + 1, r);
            }
            ++L;
        } else {
            if (pre[R] < l && nx[R] > r) {
                return ok(l, R - 1) && ok(R + 1, r);
            }
            --R;
        }
        p ^= 1;
    }
    return 0;
}

int main() {
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            pre[i] = mp[a[i]];
            mp[a[i]] = i;
        }
        mp.clear();
        for (int i = n; i >= 1; --i) {
            nx[i] = mp.find(a[i]) != mp.end() ? mp[a[i]] : n + 1;
            mp[a[i]] = i;
        }
        puts(ok(1, n) ? "non-boring" : "boring");
    }
    return 0;
}

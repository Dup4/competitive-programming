#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m = 1e5;

struct BIT {
    int a[N];
    void update(int x, int v) {
        for (; x < N; a[x] += v, x += x & -x)
            ;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; res += a[x], x -= x & -x)
            ;
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

int main() {
    cin >> n;
    int Max = 0, now = 0;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        now += bit.query(1, x - 1);
        now -= bit.query(x + 1, m);
        bit.update(x, 1);
        Max = max(Max, now);
    }
    cout << Max << " " << now << "\n";
    return 0;
}

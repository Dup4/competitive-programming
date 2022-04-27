#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m, l[N];
vector<vector<int> > a, b;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
struct node {
    ll x, y;
    node() {}
    node(ll x, ll y) : x(x), y(y) {
        ll G = gcd(x, y);
        this->x /= G;
        this->y /= G;
    }
    bool operator<(const node &other) const {
        return x * other.y < y * other.x;
    }
} res, tmp;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        a.clear();
        a.resize(max(n, m) + 1);
        b.clear();
        b.resize(max(n, m) + 1);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", l + i);
        }
        for (int i = 1, x, y; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            a[y].push_back(x);
        }
        for (int i = 1; i <= m; ++i) {
            sort(a[i].begin(), a[i].end(), [&](int x, int y) {
                return x > y;
            });
            for (int j = 0, sze = (int)a[i].size(); j < sze; ++j) {
                b[max(j + 1, l[i])].push_back(a[i][j]);
            }
        }
        res = node(0, 1);
        ll tot = 0;
        for (int i = 1; i <= n; ++i) {
            if (b[i].empty())
                continue;
            for (auto it : b[i]) {
                tot += it;
            }
            tmp = node(tot, i);
            if (res < tmp) {
                res = tmp;
            }
        }
        printf("%lld/%lld\n", res.x, res.y);
    }
    return 0;
}

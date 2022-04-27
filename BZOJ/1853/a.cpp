#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
typedef long long ll;
const int N = 1e5 + 10;
int vis[N];
ll a[N], b[N], l, r, res;

void dfs(ll x) {
    if (x > r)
        return;
    if (x)
        a[++*a] = x;
    dfs(x * 10 + 2);
    dfs(x * 10 + 9);
}

void dfs1(int cur, int cnt, ll val) {
    if (cur == *b + 1) {
        if (!cnt || !val)
            return;
        res += (r / val - (l - 1) / val) * ((cnt & 1) ? 1 : -1);
        return;
    }
    dfs1(cur + 1, cnt, val);
    if (!cnt && b[cur] <= r) {
        dfs1(cur + 1, cnt + 1, b[cur]);
        return;
    }
    ll g = __gcd(val, b[cur]);
    ll nx = val / g;
    if ((double)nx * b[cur] > r)
        return;
    dfs1(cur + 1, cnt + 1, nx * b[cur]);
}

int main() {
    cin >> l >> r;
    *a = 0, *b = 0;
    dfs(0);
    sort(a + 1, a + 1 + *a);
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= *a; ++i)
        if (!vis[i]) {
            b[++*b] = a[i];
            for (int j = i + 1; j <= *a; ++j) {
                if (a[j] % a[i] == 0)
                    vis[j] = 1;
            }
        }
    reverse(b + 1, b + 1 + *b);
    res = 0;
    dfs1(1, 0, 0);
    cout << res << endl;
    //	cout << calc(b) - calc(a - 1) << endl;
    return 0;
}

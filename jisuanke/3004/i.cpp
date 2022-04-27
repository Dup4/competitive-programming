// 3004i
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int INF = 2e9;
int n, x, y, t[N];
ll ans[N];

struct Line {
    struct node {
        ll a, b, x;
        node() {}
        node(ll a, ll b, ll x) : a(a), b(b), x(x) {}
    } t[N];
    int top;
    void init() {
        top = 0;
    }
    void insert(ll a, ll b) {
        if (!top) {
            t[++top] = node(a, b, -INF);
            return;
        }
        ll x = INF;
        while (top) {
            node tmp = t[top];
            ll cross = (tmp.b - b) / (a - tmp.a);
            if (cross >= x)
                break;
            if (cross <= t[top].x) {
                x = t[top].x;
                --top;
            } else {
                x = cross + 1;
                break;
            }
        }
        t[++top] = node(a, b, x);
    }
    ll query(ll x) {
        if (!top)
            return 0;
        int l = 1, r = top, pos = 1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (x >= t[mid].x) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return 1ll * t[pos].a * x + t[pos].b;
    }
} L;

int main() {
    while (scanf("%d%d", &n, &y) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", t + i);
        sort(t + 1, t + 1 + n, [&](int x, int y) {
            return x > y;
        });
        for (int i = 1; i <= y; ++i) ans[i] = INF;
        x = y;
        L.init();
        t[n + 1] = -y;
        for (int i = 1; i <= n + 1; ++i) {
            ll handt = t[i] + y;
            while (x >= 1) {
                ll nowt = L.query(x);
                if (nowt >= handt) {
                    ans[x] = min(ans[x], nowt);
                    --x;
                } else {
                    ans[x] = min(ans[x], handt);
                    break;
                }
            }
            L.insert(i, t[i]);
        }
        for (int i = y - 1; i >= 1; --i) ans[i] = min(ans[i], ans[i + 1]);
        for (int i = 1; i <= y; ++i) printf("%lld%c", ans[i], " \n"[i == y]);
    }
    return 0;
}

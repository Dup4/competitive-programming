#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
//#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
// void err() { cout << "\033[39;0m" << endl; }
// template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef long long ll;
#define ll int
const int N = 1e4 + 10;
const ll INF = 1e9;
int n, m, a[N];

struct LineContainer {
    struct node {
        ll a, b, x;
        node() {}
        node(ll a, ll b, ll x) : a(a), b(b), x(x) {}
    } t[N];
    int l, r, pos;
    void init() {
        l = 2, r = 1, pos = r;
    }
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    void insert(ll a, ll b) {
        if (l > r) {
            t[--l] = node(a, b, -INF);
            return;
        }
        ll x = INF;
        while (l <= r) {
            node tmp = t[r];
            if (a == tmp.a) {
                if (b <= tmp.b)
                    return;
                x = tmp.x;
                --r;
                continue;
            }
            // ll cross = div(tmp.b - b, a - tmp.a);
            ll cross = (tmp.b - b) / (a - tmp.a);
            if (cross >= x)
                break;
            if (cross > tmp.x) {
                x = cross;
                break;
            } else {
                x = tmp.x;
                --r;
            }
        }
        t[++r] = node(a, b, x);
    }
    ll query(ll x) {
        if (l > r)
            return -INF;
        if (pos > r)
            pos = r;
        while (pos < r && t[pos + 1].x <= x) ++pos;
        return t[pos].a * x + t[pos].b;
    }
} lc[5005];

int main() {
    int _T;
    scanf("%d", &_T);
    for (int kase = 1; kase <= _T; ++kase) {
        printf("Case %d: ", kase);
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        sort(a + 1, a + 1 + n);
        for (int i = 0; i <= m; ++i) lc[i].init();
        lc[0].insert(a[1] * 2, -a[1] * a[1]);
        ll res = INF;
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= 1; --j) {
                if (lc[j - 1].query(a[i]) <= -INF)
                    continue;
                ll now = lc[j - 1].query(a[i]) - a[i] * a[i];
                if (i == n && j == m)
                    res = min(res, -now);
                else
                    lc[j].insert(a[i + 1] * 2, now - a[i + 1] * a[i + 1]);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

//      ——By DD_BOND

//#include<bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#define fi first
#define se second
#define MP make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define pi 3.1415926535898
#define lowbit(a) (a & (-a))
#define lson l, (l + r) / 2, rt << 1
#define rson (l + r) / 2 + 1, r, rt << 1 | 1
#define Min(a, b, c) min(a, min(b, c))
#define Max(a, b, c) max(a, max(b, c))
#define debug(x) cerr << #x << "=" << x << "\n";

using namespace std;

typedef long long ll;
typedef pair<int, int> P;
typedef pair<ll, ll> Pll;
typedef unsigned long long ull;

const ll LLMAX = 2e18;
const int MOD = 1e9 + 7;
const double eps = 1e-12;
const int MAXN = 1e6 + 10;
const int hmod1 = 0x48E2DCE7;
const int hmod2 = 0x60000005;

inline ll sqr(ll x) {
    return x * x;
}
inline int sqr(int x) {
    return x * x;
}
inline double sqr(double x) {
    return x * x;
}
ll __gcd(ll a, ll b) {
    return b == 0 ? a : __gcd(b, a % b);
}
ll qpow(ll a, ll n) {
    ll sum = 1;
    while (n) {
        if (n & 1)
            sum = sum * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return sum;
}
inline ll dcmp(ll x) {
    if (fabs(x) < eps)
        return 0;
    return (x > 0 ? 1 : -1);
}

int p[2010];

struct Point {
    int x, y, i, j;
    Point() {
        x = y = 0;
    }
    Point(int a, int b) {
        x = a, y = b;
    }
    Point(int a, int b, Point p) {
        i = a, j = b, x = p.x, y = p.y;
    }
    Point operator-(const Point &n) const {
        return Point(x - n.x, y - n.y);
    }
    bool operator<(const Point &n) const {
        return x == n.x ? y < n.y : x < n.x;
    }
    void output() {
        cout << x << ' ' << y << endl;
    }
} point[2010], vec[2 * MAXN];

ll cross(Point a, Point b) {
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

ll check(int i, int j, int k) {
    return abs(cross(point[j] - point[i], point[k] - point[i]));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n;
    while (cin >> n) {
        ll s1 = 9e18, s2 = 0, cnt = 0;
        for (int i = 0; i < n; i++) cin >> point[i].x >> point[i].y, p[i] = i;
        if (n < 4)
            return cout << 0 << ' ' << 0 << endl, 0;
        sort(point, point + n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) vec[cnt++] = Point(i, j, point[j] - point[i]);
        sort(vec, vec + cnt, [](Point a, Point b) {
            return 1ll * a.y * b.x < 1ll * a.x * b.y;
        });
        for (int i = 0; i < cnt; i++) {
            int a = vec[i].i, b = vec[i].j;
            if (p[a] > p[b])
                swap(a, b);
            if (p[a] != 0 && p[b] != n - 1)
                s2 = max(s2, check(p[a], p[b], 0) + check(p[a], p[b], n - 1));
            if (p[a] != 0 && p[b] != n - 1)
                s1 = min(s1, check(p[a], p[b], p[a] - 1) + check(p[a], p[b], p[b] + 1));
            swap(p[a], p[b]);
            swap(point[p[a]], point[p[b]]);
        }
        cout << s1 << ' ' << s2 << endl;
    }
    return 0;
}

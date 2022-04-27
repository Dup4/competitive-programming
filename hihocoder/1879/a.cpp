#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
const int N = 5e3 + 10;
const ll mod = 998244353;
int n;
LL sumx[N], sumy[N];

ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

struct Point {
    LL x, y;
    Point() {}
    Point(LL x, LL y) : x(x), y(y) {}
    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }
    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
    LL operator^(const Point &other) const {
        return x * other.y - y * other.x;
    }
    bool operator<(const Point &other) const {
        if (y < 0 && other.y > 0)
            return true;
        if (y > 0 && other.y < 0)
            return false;
        if (y == 0 && other.y == 0) {
            return (x < 0 && other.x > 0);
        } else {
            return ((*this) ^ other) > 0;
        }
    }
} p[N], qrr[N];

ll gao() {
    LL res1 = 0, res2 = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= n; ++j)
            if (i != j) {
                qrr[++cnt] = p[j] - p[i];
            }
        sort(qrr + 1, qrr + 1 + cnt);
        for (int j = 1; j <= cnt; ++j) {
            qrr[j + cnt] = qrr[j];
        }
        sumx[0] = sumy[0] = 0;
        cnt <<= 1;
        for (int j = 1; j <= cnt; ++j) {
            sumx[j] = (sumx[j - 1] + qrr[j].x) % mod;
            sumy[j] = (sumy[j - 1] + qrr[j].y) % mod;
        }
        int q = 1, s = 1, t = 1;
        for (int j = 1; j < n; ++j) {
            q = max(q, j);
            Point _90 = Point(-qrr[j].y, qrr[j].x);
            Point _180 = Point(-qrr[j].x, -qrr[j].y);
            //重合分界线
            while (q < cnt && (qrr[q + 1] ^ qrr[j]) == 0) ++q;
            //(q, s] 锐角范围
            while (s < cnt && (s < q || ((qrr[s + 1] ^ _90) > 0 && (qrr[s + 1] ^ qrr[j]) <= 0))) ++s;
            //(s, t] 直角钝角范围
            while (t < cnt && (t < s || ((qrr[t + 1] ^ _180) > 0 && (qrr[t + 1] ^ _90) <= 0))) ++t;
            res1 = (res1 + (sumy[s] - sumy[q] + mod) % mod * (qrr[j].x % mod) % mod -
                           (sumx[s] - sumx[q] + mod) % mod * (qrr[j].y) % mod + mod) %
                   mod;
            res2 = (res2 + (sumy[t] - sumy[s] + mod) % mod * (qrr[j].x % mod) % mod -
                           (sumx[t] - sumx[s] + mod) % mod * (qrr[j].y) % mod + mod) %
                   mod;
        }
    }
    return ((res1 - res2 * 2 % mod + mod) % mod * qpow(3, mod - 2) % mod) % mod;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            ll x, y;
            scanf("%lld%lld", &x, &y);
            p[i].x = x;
            p[i].y = y;
        }
        printf("%lld\n", gao());
    }
    return 0;
}

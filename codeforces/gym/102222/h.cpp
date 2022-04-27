#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int n;
ll bit[N];
struct node {
    ll a, b, t;
    node() {}
    void scan() {
        scanf("%lld%lld", &a, &b);
        t = lower_bound(bit + 1, bit + N, a) - bit;
    }
    bool operator<(const node &other) const {
        ll pre = b * t + other.b * (t + other.t);
        ll nx = other.b * other.t + b * (t + other.t);
        return pre < nx;
    }
} a[N];

int main() {
    bit[1] = 1;
    for (int i = 2; i < N; ++i) {
        bit[i] = bit[i - 1] + i;
    }
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) a[i].scan();
        ll res = 0;
        sort(a + 1, a + 1 + n);
        ll t = 0;
        for (int i = 1; i <= n; ++i) {
            t += a[i].t;
            res += a[i].b * t;
        }
        printf("%lld\n", res);
    }
    return 0;
}

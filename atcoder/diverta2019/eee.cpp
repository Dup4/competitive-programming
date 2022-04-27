#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define M 2000010
const ll p = 1e9 + 7;
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}
int n, a[N], b[N];
vector<vector<int> > vec;

int main() {
    while (scanf("%d", &n) != EOF) {
        vec.clear();
        int Max = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            a[i] ^= a[i - 1];
            Max = max(Max, a[i]);
            // printf("%d%c", a[i], " \n"[i == n]);
        }
        vec.resize(Max + 1);
        for (int i = 1; i <= n; ++i) {
            vec[a[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i) {
            b[i] = (a[i] == 0);
            b[i] += b[i - 1];
        }
        ll res = 0;
        if (a[n] == 0) {
            res = qmod(2, (int)vec[a[0]].size() - 1);
            for (int i = 1; i <= Max; ++i)
                if (!vec[i].empty()) {
                    ll base = 0;
                    ll tot = 0;
                    int pre = 0;
                    ll tmp = 0;
                    for (auto it : vec[i]) {
                        ll zero = b[it] - b[pre];
                        pre = it;
                        (tot += zero * base % p) %= p;
                        tmp = (tot + 1) % p;
                        (base += tmp) %= p;
                        (res += tmp) %= p;
                    }
                }
        } else {
            ll base = 0;
            ll tot = 0;
            int pre = 0;
            for (auto it : vec[a[n]]) {
                ll zero = b[it] - b[pre];
                pre = it;
                (tot += zero * base % p) %= p;
                res = (tot + 1) % p;
                (base += res) %= p;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}

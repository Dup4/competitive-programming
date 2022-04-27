#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n;
ll k, p, a[N];
map<ll, int> mp;

int main() {
    while (scanf("%d%lld%lld", &n, &p, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
            a[i] = (a[i] * a[i] % p * a[i] % p * a[i] % p - k * a[i] % p + p) % p;
        }
        mp.clear();
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            if (mp.find(a[i]) != mp.end()) {
                res += mp[a[i]];
            }
            ++mp[a[i]];
        }
        printf("%lld\n", res);
    }
    return 0;
}

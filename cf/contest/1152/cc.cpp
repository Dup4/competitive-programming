#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    ll a, b;
    while (scanf("%lld%lld", &a, &b) != EOF) {
        ll Min = a * b / gcd(a, b);
        int pos = 0;
        if (a > b) {
            swap(a, b);
        }
        vector<int> fac;
        ll t = b - a;
        for (int i = 1; 1ll * i * i <= t; ++i) {
            if (t % i == 0) {
                fac.push_back(i);
                fac.push_back(t / i);
            }
        }
        sort(fac.begin(), fac.end());
        fac.erase(unique(fac.begin(), fac.end()), fac.end());
        for (auto it : fac) {
            int y = a % it;
            int k = it - y;
            ll tmp = (a + k) * (b + k) / gcd((a + k), (b + k));
            if (tmp < Min || (tmp == Min && pos < k)) {
                Min = tmp;
                pos = k;
            }
        }
        printf("%d\n", pos);
    }
    return 0;
}

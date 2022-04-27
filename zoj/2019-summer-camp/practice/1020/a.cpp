#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
int n;
map<int, int> mp;

void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
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

ll DFS(int n) {
    if (mp.find(n) != mp.end())
        return mp[n];
    ll res = n;
    for (int i = 2, j; i <= n; i = j + 1) {
        j = n / (n / i);
        add(res, 1ll * (j - i + 1) * DFS(n / i) % p);
    }
    return mp[n] = res * qmod(n - 1, p - 2) % p;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        mp.clear();
        mp[1] = 1;
        printf("%lld\n", DFS(n));
    }
    return 0;
}

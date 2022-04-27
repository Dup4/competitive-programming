#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, k;
ll sum(ll n) {
    return n * (n + 1) / 2;
}

int main() {
    cin >> n >> k;
    ll res = n * k;
    for (int i = 1, j; i <= min(n, k); i = j + 1) {
        j = min(k / (k / i), n);
        res -= (sum(j) - sum(i - 1)) * (k / i);
    }
    cout << res << "\n";
    return 0;
}

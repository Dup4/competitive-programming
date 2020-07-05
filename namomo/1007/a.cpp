#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int a[N];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n * 2; ++i) scanf("%d", a + i);
    sort(a + 1, a + 1 + n * 2);
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= 1ll * (a[i] + a[n * 2 - i + 1]);
        res %= mod;
    }
    cout << res << endl;
    return 0;
}
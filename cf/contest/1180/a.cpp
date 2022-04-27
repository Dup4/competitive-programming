#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll f[220];

int main() {
    f[1] = 1;
    ll base = 0;
    for (int i = 2; i <= 100; ++i) {
        base += 4;
        f[i] = f[i - 1] + base;
    }
    int n;
    while (cin >> n) {
        cout << f[n] << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double

int main() {
    db eps;
    cin >> eps;
    db res = 1;
    ll x = 1;
    for (int i = 1;; ++i) {
        x *= i;
        if ((1.0 / x) < eps) {
            break;
        }
        res += 1.0 / x;
    }
    cout << fixed << setprecision(6) << res << endl;
    return 0;
}

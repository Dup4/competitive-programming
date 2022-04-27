#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool gao(int x) {
    int limit = 5000;
    for (ll a = -limit; a <= limit; ++a) {
        for (ll b = a; b <= limit; ++b) {
            for (ll c = b; c <= limit; ++c) {
                ll a3 = a * a * a;
                ll b3 = b * b * b;
                ll c3 = c * c * c;
                ll sum = a3 + b3 + c3;
                if (sum > x)
                    break;
                if (sum == x) {
                    cout << a << " " << b << " " << c << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int cnt = 0;
    int Y = -12345678;
    for (int i = 0; i <= 200; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == Y) {
            if (!gao(x)) {
                ++cnt;
                printf("%d %d %d\n", Y, Y, Y);
            }
        } else {
            cout << x << " " << y << " " << z << endl;
        }
    }
    cout << cnt << " " << cnt << " " << cnt << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    int mod = 111111111, T, u, v, s;
    cin >> T;
    while (T--) {
        s = 0;
        v = mod;
        cin >> u;
        while (1) {
            while (u < v) {
                v /= 10;
            }
            if (u == 0 || v == 0)
                break;

            s += u / v;
            u -= (u / v) * v;
        }
        if (s < 10)
            cout << s << endl;
        else
            cout << "Impossible" << endl;
    }
    return 0;
}

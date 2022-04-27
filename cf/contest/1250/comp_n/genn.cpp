#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
    int T = 10, m = 1000000000;
    cout << T << endl;
    while (T--) {
        int n = 1000;
        cout << n << endl;
        for (int i = 1; i <= n; ++i) {
            int x = rnd() % m + 1, y = rnd() % m + 1;
            while (x == 1) x = rnd() % m + 1;
            while (y == x || y == 1) y = rnd() % m + 1;
            cout << x << " " << y << endl;
        }
    }
    return 0;
}

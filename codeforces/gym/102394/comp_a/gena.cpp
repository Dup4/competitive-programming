#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}
int main() {
    int T = 2;
    cout << T << endl;
    while (T--) {
        int n = 1500, M1 = 1500, M2 = 1500;
        cout << n << " " << M1 << " " << M2 << endl;
        for (int i = 1; i <= M1; ++i) {
            int l = random(1, n), r = random(1, n);
            if (l > r)
                swap(l, r);
            int k = random(0, r - l + 1);
            if (k > 10)
                k = 10;
            cout << l << " " << r << " " << k << endl;
        }
        for (int i = 1; i <= M1; ++i) {
            int l = random(1, n), r = random(1, n);
            if (l > r)
                swap(l, r);
            int k = random(0, n - (r - l + 1));
            if (k > 10)
                k = 10;
            cout << l << " " << r << " " << k << endl;
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int main() {
    int n = 3, q = 20;
    cout << n << " " << q << endl;
    for (int i = 1; i <= n; ++i) cout << random(1, n) << " \n"[i == n];
    for (int i = 1; i <= q; ++i) {
        int op = random(1, 3);
        cout << op;
        if (op < 3) {
            int l = random(1, n), r = random(1, n);
            if (l > r)
                swap(l, r);
            cout << " " << l << " " << r << endl;
        } else {
            int x = random(1, n);
            cout << " " << x << endl;
        }
    }
    return 0;
}

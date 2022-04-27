#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}
int main() {
    int T = 5;
    cout << T << endl;
    while (T--) {
        int n = 10, q = 10;
        cout << n << endl;
        for (int i = 2; i <= n; ++i) cout << i << " " << random(1, i - 1) << endl;
        cout << q << endl;
        while (q--) {
            int op = random(1, 3);
            if (op == 1) {
                int x = random(1, 10), l = random(1, n), r = random(1, n);
                if (l > r)
                    swap(l, r);
                cout << op << " " << x << " " << l << " " << r << endl;
            } else if (op == 2) {
                int x = random(1, 10);
                cout << op << " " << x << endl;
            } else {
                int x = random(1, n), p = random(1, 5);
                cout << op << " " << x << " " << p;
                for (int i = 1; i <= p; ++i) cout << " " << random(1, n);
                cout << endl;
            }
        }
    }
    return 0;
}

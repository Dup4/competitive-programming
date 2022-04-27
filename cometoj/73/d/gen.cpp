#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int main() {
    int n = 5, m = 5, q = 5;
    cout << n << " " << m << " " << q << endl;
    for (int i = 1; i <= n; ++i) {
        int l = random(1, n), r = random(1, n), v = random(1, 1000000000);
        if (l > r)
            swap(l, r);
        cout << l << " " << r << " " << v << endl;
    }
    for (int i = 1; i <= q; ++i) {
        int l = random(1, n), r = random(1, n);
        if (l > r)
            swap(l, r);
        cout << l << " " << r << endl;
    }
    return 0;
}

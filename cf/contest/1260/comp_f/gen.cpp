#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}
const int N = 1e5 + 10;
int l[N], r[N];
int main() {
    int n = 100000;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        l[i] = random(1, 100000), r[i] = random(1, 100000);
        if (l[i] > r[i])
            swap(l[i], r[i]);
        cout << l[i] << " " << r[i] << endl;
    }
    for (int i = 2; i <= n; ++i) {
        cout << i << " " << random(1, i - 1) << endl;
    }
}

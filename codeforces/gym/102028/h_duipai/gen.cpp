#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
inline int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}
int main() {
    cout << 10 << endl;
    for (int _i = 1; _i <= 10; ++_i) {
        int n = random(2, 20);
        cout << n << endl;
        cout << 1000000 << " ";
        for (int i = 2; i <= n; ++i) cout << random(1, 1000000) << " \n"[i == n];
    }
}

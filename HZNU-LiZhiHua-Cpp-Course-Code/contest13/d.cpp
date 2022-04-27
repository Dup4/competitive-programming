#include <bits/stdc++.h>
using namespace std;

bool ok(int x) {
    int tot = 0;
    int t = x;
    while (t) {
        tot += t % 10;
        t /= 10;
    }
    return x % tot == 0;
}

int main() {
    int n;
    cin >> n;
    for (int i = 10; i <= n; ++i) {
        if (ok(i)) {
            cout << i << "\n";
        }
    }
    return 0;
}

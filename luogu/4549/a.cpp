#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n;
    int G = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        G = __gcd(G, abs(x));
    }
    cout << G << endl;
    return 0;
}

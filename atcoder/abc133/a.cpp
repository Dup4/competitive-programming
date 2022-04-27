#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    while (cin >> n >> a >> b) {
        cout << min(n * a, b) << "\n";
    }
    return 0;
}

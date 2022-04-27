#include <bits/stdc++.h>
using namespace std;

int main() {
    int T = 1;
    cout << T << endl;
    int n = 1e6;
    cout << n << endl;
    for (int j = 1; j <= 2; ++j) {
        int sze = 5e5;
        cout << 1 << " " << sze;
        for (int i = 1; i <= sze; ++i) cout << " " << i;
        cout << endl;
    }
    for (int j = 3; j <= n; ++j) {
        cout << "2 1 " << j - 1 << endl;
    }
    return 0;
}

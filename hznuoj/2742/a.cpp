#include <bits/stdc++.h>
using namespace std;
int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        int n, x, y, A, B;
        cin >> n;
        int res = 0;
        string s;
        cin >> s >> x >> y;
        for (int i = 2; i <= n; ++i) {
            cin >> A >> B;
            res += (A < x) & (B < y);
        }
        cout << res << endl;
    }
    return 0;
}

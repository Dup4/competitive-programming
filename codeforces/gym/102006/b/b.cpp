#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("hamming.in", "r", stdin);
    int _T;
    cin >> _T;
    string s, t;
    while (_T--) {
        int n;
        cin >> n;
        cin >> s >> t;
        int a[2] = {0, 0}, b[2] = {0, 0};
        for (auto &c : s) ++a[c - '0'];
        for (auto &c : t) ++b[c - '0'];
        cout << min(a[0], b[1]) + min(a[1], b[0]) << "\n";
    }
    return 0;
}

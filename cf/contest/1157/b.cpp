#include <bits/stdc++.h>
using namespace std;

int n;
int f[11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n) {
        string s;
        cin >> s;
        for (int i = 1; i <= 9; ++i) {
            cin >> f[i];
        }
        string res = s, t = "";
        for (int i = 1; i <= 9; ++i) {
            t = s;
            for (int j = 0; j < n; ++j) {
                if (t[j] == i + '0') {
                    t[j] = f[i] + '0';
                }
            }
            res = max(res, t);
        }
        cout << res << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        int n, m, c;
        cin >> n >> m >> c;
        map<string, int> mp;
        for (int i = 1; i <= n; ++i) {
            string s;
            int a, b;
            cin >> s >> a >> b;
            mp[s] = a - b;
        }
        for (int i = 1; i <= m; ++i) {
            int q;
            cin >> q;
            while (q--) {
                string s;
                int cnt;
                cin >> s >> cnt;
                c -= mp[s] * cnt;
            }
        }
        if (c <= 0)
            cout << "heiheihei\n";
        else
            cout << "awysl\n";
    }
    return 0;
}

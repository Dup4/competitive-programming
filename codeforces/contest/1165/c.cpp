#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
char s[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n) {
        cin >> (s + 1);
        string res = "";
        int tot = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] != s[i + 1]) {
                if (i == n - 1) {
                    --tot;
                }
                res += s[i];
                res += s[i + 1];
                ++i;
            } else {
                ++tot;
            }
        }
        cout << tot << "\n";
        cout << res << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
const int mod = 1e9 + 7;
int n;
string s, t = "acpty";
void run() {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        int len = s.size();
        if (len >= 5) {
            bool F = 1;
            for (int j = 0; j < 5; ++j) {
                if (t[j] != s[len - 5 + j])
                    F = 0;
            }
            res += F;
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
int n, a[N];
char s[N];
void run() {
    memset(a, 0, sizeof a);
    cin >> (s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'L') {
            for (int j = 0; j <= 9; ++j) {
                if (a[j] == 0) {
                    a[j] = 1;
                    break;
                }
            }
        } else if (s[i] == 'R') {
            for (int j = 9; j >= 0; --j) {
                if (a[j] == 0) {
                    a[j] = 1;
                    break;
                }
            }
        } else {
            a[s[i] - '0'] = 0;
        }
    }
    for (int i = 0; i <= 9; ++i) cout << a[i];
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) run();
    return 0;
}

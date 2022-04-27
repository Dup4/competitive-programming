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
int n, m, k, h[N];
void run() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    for (int i = 1; i < n; ++i) {
        if (h[i] < h[i + 1]) {
            if (h[i + 1] - h[i] > k) {
                if (m < (h[i + 1] - h[i] - k)) {
                    cout << "NO\n";
                    return;
                } else {
                    m -= h[i + 1] - h[i] - k;
                }
            } else {
                m += min(k - (h[i + 1] - h[i]), h[i]);
            }
        } else {
            m += h[i] - h[i + 1];
            m += min(k, h[i + 1]);
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) run();
    return 0;
}

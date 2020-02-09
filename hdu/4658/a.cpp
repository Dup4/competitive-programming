#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;
int ans[N];
void init() {
    memset(ans, 0, sizeof(ans));
    ans[0] = 1;
    for (int i = 1; i < N; ++i) {
        ans[i] = 0;
        for (int j = 1; ; j++) {
            int tmp = (3 * j - 1) * j / 2;
            if (tmp > i) break;
            int _tmp = ans[i - tmp];
            if (tmp + j <= i) {
                _tmp = (_tmp + ans[i - tmp - j]) % mod;
            }
            if (j & 1) {
                ans[i] = (ans[i] + _tmp) % mod;
            } else {
                ans[i] = (ans[i] - _tmp + mod) % mod;
            }
        }
    }
}

int solve(int n, int k) {
    int res = ans[n];
    for (int i = 1; ; i++) {
        int tmp = k * i * (3 * i - 1) / 2;
        if (tmp > n) {
            break;
        }
        int _tmp = ans[n - tmp];
        if (tmp + i * k <= n) {
            _tmp = (_tmp + ans[n - tmp - i * k]) % mod;
        }
        if (i & 1) {
            res = (res - _tmp + mod) % mod;
        } else {
            res = (res + _tmp) % mod;
        }
    }
    return res;
}

int main() {
    init();
    int _T, n, k;
    cin >> _T;
    while (_T--) {
        cin >> n >> k;
        cout << solve(n, k) << '\n';
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
int x[N], y[N];

int main() {
    while (cin >> n) {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i];
            res = max(res, x[i] * y[i]);
            for (int j = 1; j < i; ++j) {
                res = max(res, 2 * min(x[i], x[j]) * min(y[i], y[j]));
                res = max(res, 2 * min(x[i], y[j]) * min(y[i], x[j]));
            }
        }
        printf("%.1f\n", res / 2.0);
    }
    return 0;
}

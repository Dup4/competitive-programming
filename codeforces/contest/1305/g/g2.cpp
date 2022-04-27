#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n, a[N], use[N];

int main() {
    memset(use, 0, sizeof use);
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    sort(a + 1, a + 1 + n, [](int x, int y) {
        return x > y;
    });
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (use[i] == 0) {
            for (int j = i + 1; j <= n; ++j)
                if (use[j]) {
                    if ((a[i] & a[j]) == 0) {
                        res += a[j];
                        break;
                    }
                }
            use[i] = 1;
        }
        for (int j = i + 1; j <= n; ++j)
            if (use[j] == 0) {
                if ((a[i] & a[j]) == 0) {
                    res += a[i];
                    use[j] = 1;
                }
            }
    }
    cout << res << endl;
    return 0;
}

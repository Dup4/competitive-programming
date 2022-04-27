#include <bits/stdc++.h>

using namespace std;

#define N 50

int n;
int a[N], vis[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        a[i] = i;
    }
    double res = 0;
    do {
        int limit = 1000, cnt = 0;
        for (int cas = 1; cas <= limit; ++cas) {
            for (int i = 1; i <= n; ++i) {
                vis[i] = 0;
            }
            for (int i = 1; i <= n; ++i) {
                if (a[i] != 1 || vis[a[i]]) {
                    int tmp = rand() % (n - i + 1) + 1;
                    for (int j = 1, k = 0; j <= n; ++j) {
                        if (!vis[j]) {
                            ++k;
                            if (k == tmp) {
                                vis[j] = a[i];
                                break;
                            }
                        }
                    }
                } else {
                    vis[a[i]] = a[i];
                }
            }
            if (vis[a[n]] == a[n])
                cnt++;
        }
        res += cnt * 1.0 / 1000;
    } while (next_permutation(a + 1, a + 1 + n));
    double ans = res;
    cout << ans << endl;
    for (int i = 1; i <= n; ++i) {
        ans /= i;
    }
    cout << ans << endl;
    return 0;
}

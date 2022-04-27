#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n, [&](int x, int y) {
            if ((x & 1) != (y & 1)) {
                return (x & 1) > (y & 1);
            } else {
                return x < y;
            }
        });
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
    }
    return 0;
}

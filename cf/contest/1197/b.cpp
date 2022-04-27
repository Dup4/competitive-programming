#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        int pos = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i] > a[pos])
                pos = i;
        }
        int l = pos - 1, r = pos + 1;
        bool F = 1;
        int lst = a[pos];
        while (l >= 1 || r <= n) {
            if (l < 1) {
                if (a[r] >= lst) {
                    F = 0;
                    break;
                }
                lst = a[r];
                ++r;
            } else if (r > n) {
                if (a[l] >= lst) {
                    F = 0;
                    break;
                }
                lst = a[l];
                --l;
            } else {
                if (a[l] > a[r]) {
                    if (a[l] >= lst) {
                        F = 0;
                        break;
                    }
                    lst = a[l];
                    --l;
                } else {
                    if (a[r] >= lst) {
                        F = 0;
                        break;
                    }
                    lst = a[r];
                    ++r;
                }
            }
        }
        puts(F ? "YES" : "NO");
    }
    return 0;
}

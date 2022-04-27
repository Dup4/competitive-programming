#include <bits/stdc++.h>
using namespace std;

const int N = 1e2 + 10;
int n, a[N], b[N];

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            a[i] %= 3;
        }
        *b = 0;
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0)
                ++res;
            else {
                if (*b && a[i] + b[*b] == 3) {
                    --*b;
                    ++res;
                } else {
                    b[++*b] = a[i];
                }
            }
        }
        res += *b / 3;
        printf("%d\n", res);
    }
    return 0;
}

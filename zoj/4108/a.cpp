#include <bits/stdc++.h>
using namespace std;

#define N 10010
char a[N], b[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", a + 1, b + 1);
        int l = 0, r = 0;
        for (int i = 1, len = strlen(a + 1); i <= len; ++i) {
            l = (l * 10 + a[i] - '0') % 3;
        }
        for (int i = 1, len = strlen(b + 1); i <= len; ++i) {
            r = (r * 10 + b[i] - '0') % 3;
        }
        int t[] = {2, 1, 2};
        printf("%d\n", (t[r] - t[(l + 2) % 3] + 2) % 2);
    }
    return 0;
}

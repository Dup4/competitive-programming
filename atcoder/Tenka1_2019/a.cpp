#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define INF 0x3f3f3f3f
int n;
char s[N];
int f[N][2];

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        f[0][0] = 0;
        f[1][0] = 0;
        f[1][1] = 1;
        for (int i = 2; i <= n; ++i) {
            // white
            if (s[i] == '.') {
                if (s[i - 1] == '.') {
                    f[i][0] = f[i - 1][0];
                } else {
                    f[i][0] = f[i - 1][1];
                }
                f[i][1] = min(f[i - 1][0], f[i - 1][1]) + 1;
            } else {
                f[i][0] = min(f[i - 1][0], f[i - 1][1]);
                if (s[i - 1] == '.') {
                    f[i][1] = f[i - 1][0] + 1;
                } else {
                    f[i][1] = f[i - 1][1] + 1;
                }
            }
        }
        printf("%d\n", min(f[n][0], f[n][1]));
    }
    return 0;
}

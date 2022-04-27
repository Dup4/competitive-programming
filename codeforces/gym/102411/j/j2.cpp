#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
int n, a[N][N], g[N][N];
char s[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            for (int j = 1; j <= n; ++j) {
                a[i][j] = s[j] - '0';
            }
        }
        memset(g, 0, sizeof g);
        for (int i = 1; i <= n; ++i) {
        }
    }
    return 0;
}

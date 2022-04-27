#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int ALP = 26;
int n, m;
char s[N], t[N];
int f[N][ALP], nx[220];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        scanf("%s%s", s + 1, t + 1);
        for (int i = 0; i < 220; ++i) nx[i] = n + 1;
        for (int i = n; i >= 0; --i) {
            for (int j = 0; j < ALP; ++j) f[i][j] = nx[j];
            if (i)
                nx[s[i] - 'a'] = i;
        }
        int res = -1;
        for (int i = 1, u = 0; i <= m + 1; ++i) {
            int c;
            if (i == m + 1)
                c = -1;
            else
                c = t[i] - 'a';
            int p = INF;
            for (int j = c + 1; j < ALP; ++j) {
                if (f[u][j] <= n) {
                    p = min(p, f[u][j]);
                }
            }
            if (p != INF)
                res = max(res, i + n - p);
            if (i == m + 1)
                break;
            if (f[u][c] <= n)
                u = f[u][c];
            else
                break;
        }
        printf("%d\n", res);
    }
    return 0;
}

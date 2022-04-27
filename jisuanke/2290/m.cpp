#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m, q;
char s[N], t[N];
int T[N][30], nx[30];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        for (int i = 0; i < 30; ++i) nx[i] = n + 1;
        for (int i = n; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) {
                T[i][j] = nx[j];
            }
            if (i) {
                nx[s[i] - 'a'] = i;
            }
        }
        scanf("%d", &q);
        while (q--) {
            scanf("%s", t + 1);
            m = strlen(t + 1);
            int it = 0;
            for (int i = 1; i <= m; ++i) {
                it = T[it][t[i] - 'a'];
                if (it == n + 1)
                    break;
            }
            puts(it == n + 1 ? "NO" : "YES");
        }
    }
    return 0;
}

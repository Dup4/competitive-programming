#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], res[N];
int nx[N][26];
int n, m, len;

void add(int now) {
    for (int i = now; i <= len; ++i) {
        res[++m] = s[i];
        for (int j = m - 1; j >= 0; --j) {
            nx[j][res[m] - 'a'] = m;
            if (res[j] == s[i]) {
                break;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        m = 0;
        memset(nx, -1, sizeof nx);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            len = strlen(s + 1);
            if (i == 1) {
                add(1);
            } else {
                int now = 0;
                for (int j = 1; j <= len; ++j) {
                    now = nx[now][s[j] - 'a'];
                    if (now == -1) {
                        add(j);
                        break;
                    }
                }
            }
        }
        res[m + 1] = 0;
        printf("%s\n", res + 1);
    }
    return 0;
}

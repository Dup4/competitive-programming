#include <bits/stdc++.h>

#define LL long long
#define pa pair<int, int>
using namespace std;
const int inf = 2147483647;

int _max(int x, int y) {
    return x > y ? x : y;
}
int _min(int x, int y) {
    return x < y ? x : y;
}
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return x * f;
}
void put(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        put(x / 10);
    putchar(x % 10 + '0');
}

char ss[1001];
int s[1001][1001], ans[2001];
int tp1, st1[1001], tp2, st2[1001];

int main() {
    //	freopen("a.in", "r", stdin);
    //	freopen("a.out", "w", stdout);
    int T = read();
    while (T--) {
        int n = read(), m = read(), k = read();
        for (int i = 1; i <= n; i++) {
            scanf("%s", ss + 1);
            for (int j = 1; j <= m; j++) {
                if (ss[j] == '1')
                    s[i][j] = 0;
                else
                    s[i][j] = 1;
                s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            }
        }
        if (!s[n][m]) {
            for (int i = 1; i < k; i++) put(i), putchar(' ');
            put(k), puts("");
            continue;
        }
        bool zz = 0;
        for (int i = _min(n - 1, k); i >= 0; i--)
            if (s[n][m] % ((i + 1) * (k - i + 1)) == 0) {
                int h1 = s[n][m] / (i + 1), h2 = s[n][m] / (k - i + 1), hh = h1 / (k - i + 1), S = 0;
                tp1 = tp2 = 0;
                for (int j = 1; j <= n; j++)
                    if (s[j][m] != s[j - 1][m]) {
                        if (s[j][m] % h1 == 0)
                            S++, st1[++tp1] = j;
                    }
                if (S != i + 1)
                    continue;
                S = 0;
                for (int j = 1; j <= m; j++)
                    if (s[n][j] != s[n][j - 1]) {
                        if (s[n][j] % h2 == 0)
                            S++, st2[++tp2] = j;
                    }
                if (S != k - i + 1)
                    continue;
                bool bk = 0;
                for (int j = 1; j <= tp1; j++) {
                    for (int h = 1; h <= tp2; h++) {
                        if (s[st1[j]][st2[h]] - s[st1[j - 1]][st2[h]] - s[st1[j]][st2[h - 1]] +
                                        s[st1[j - 1]][st2[h - 1]] !=
                                hh) {
                            bk = 1;
                            break;
                        }
                    }
                    if (bk)
                        break;
                }
                int v = 0;
                if (!bk) {
                    for (int j = 1; j < tp1; j++) ans[++v] = st1[j];
                    for (int j = 1; j < tp2; j++) ans[++v] = st2[j] + n - 1;
                    for (int i = 1; i < v; i++) put(ans[i]), putchar(' ');
                    put(ans[v]), puts("");
                    zz = 1;
                    break;
                }
            }
        if (!zz)
            puts("Impossible");
    }
    return 0;
}

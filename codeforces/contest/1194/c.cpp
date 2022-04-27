#include <bits/stdc++.h>
using namespace std;

#define N 110
char s[N], t[N], p[N];
int cnts[30], cntt[30], cntp[30], lens, lent, lenp;
int nx[30], f[N][30];

bool ok() {
    for (int i = 0; i < 26; ++i) {
        if (cnts[i] > cntt[i] || cnts[i] + cntp[i] < cntt[i])
            return 0;
    }
    for (int i = 0; i < 26; ++i) nx[i] = lent + 1;
    for (int i = lent; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            f[i][j] = nx[j];
        }
        if (i)
            nx[t[i] - 'a'] = i;
    }
    int it = 0;
    for (int i = 1; i <= lens; ++i) {
        it = f[it][s[i] - 'a'];
        if (it == lent + 1)
            break;
    }
    return (it != lent + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s%s", s + 1, t + 1, p + 1);
        lens = strlen(s + 1);
        lent = strlen(t + 1);
        lenp = strlen(p + 1);
        memset(cnts, 0, sizeof cnts);
        memset(cntt, 0, sizeof cntt);
        memset(cntp, 0, sizeof cntp);
        for (int i = 1; i <= lens; ++i) ++cnts[s[i] - 'a'];
        for (int i = 1; i <= lent; ++i) ++cntt[t[i] - 'a'];
        for (int i = 1; i <= lenp; ++i) ++cntp[p[i] - 'a'];
        puts(ok() ? "YES" : "NO");
    }
    return 0;
}

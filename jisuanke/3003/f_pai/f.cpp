#include <bits/stdc++.h>
using namespace std;

int n;
char s[30];
__int128 f[30][30][30], K;
template <class T>
void rd(T &x) {
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()))
        ;
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}
template <class T>
void out(T x) {
    if (x / 10)
        out(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    memset(f, 0, sizeof f);
    for (int n = 1; n <= 26; ++n) {
        for (int i = n; i >= 1; --i) {
            if (i == n) {
                for (int j = 1; j <= i; ++j) f[n][i][j] = 1;
            } else {
                for (int j = 1; j <= i; ++j) {
                    f[n][i][j] = f[n][i + 1][j] * j + f[n][i + 1][j + 1];
                }
            }
        }
    }
    int _T;
    scanf("%d", &_T);
    for (int kase = 1; kase <= _T; ++kase) {
        printf("Case #%d: A", kase);
        rd(n), rd(K);
        int Max = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= Max + 1; ++j) {
                if (K > f[n][i + 1][max(Max, j)])
                    K -= f[n][i + 1][max(Max, j)];
                else {
                    s[i] = 'A' + j - 1;
                    Max = max(Max, j);
                    break;
                }
            }
        }
        s[n] = 0;
        printf("%s\n", s + 1);
    }
    return 0;
}

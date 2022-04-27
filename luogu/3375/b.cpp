#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N], t[N];
int Next[N], NextVal[N];

void get_next(char *s) {
    int len = strlen(s);
    int i, j;
    j = Next[0] = -1;
    i = 0;
    while (i < len) {
        while (j != -1 && s[i] != s[j]) j = Next[j];
        Next[++i] = ++j;
    }
}

void get_nextval(char *s) {
    int len = strlen(s);
    int i, j;
    j = NextVal[0] = -1;
    i = 0;
    while (i < len) {
        while (j != -1 && s[i] != s[j]) j = NextVal[j];
        NextVal[++i] = ++j;
        if (NextVal[i] >= 0 && s[i] == s[NextVal[i]])
            NextVal[i] = NextVal[NextVal[i]];
    }
}

void kmp(char *s, char *t) {
    int lens = strlen(s), lent = strlen(t);
    get_next(t);
    get_nextval(t);
    int i, j;
    i = j = 0;
    while (i < lens) {
        while (-1 != j && s[i] != t[j]) j = NextVal[j];
        ++i, ++j;
        if (j >= lent) {
            printf("%d\n", i - lent + 1);
            j = NextVal[j];
        }
    }
}

int main() {
    scanf("%s%s", s, t);
    kmp(s, t);
    int lent = strlen(t);
    for (int i = 1; i <= lent; ++i) printf("%d%c", Next[i], " \n"[i == lent]);
    return 0;
}

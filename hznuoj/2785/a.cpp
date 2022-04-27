#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
char s[N], t[N];

bool gao() {
    scanf("%s%s", s, t);
    int i = 0, j = 0, slen = strlen(s), tlen = strlen(t);
    while (i < slen && j < tlen) {
        if (s[i] == t[j]) {
            ++i, ++j;
            continue;
        }
        if (!isdigit(t[j]) && s[i] != t[j])
            return false;
        i += (t[j++] - '0');
    }
    return i == slen && j == tlen;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) puts(gao() ? "True" : "False");
    return 0;
}

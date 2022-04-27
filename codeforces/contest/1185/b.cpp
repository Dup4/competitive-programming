#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], t[N];

bool ok() {
    int len1 = strlen(s), len2 = strlen(t);
    if (len2 < len1) {
        return false;
    }
    int i = 0, j = 0;
    for (; i < len1; ++i) {
        while (s[i] != t[j] && j > 0 && j < len2 && t[j] == t[j - 1]) {
            ++j;
        }
        if (j > len2 - 1) {
            return false;
        }
        if (s[i] == t[j]) {
            ++j;
        } else {
            return false;
        }
    }
    for (; j < len2; ++j) {
        if (j == 0) {
            return false;
        }
        if (t[j] != t[j - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s, t);
        puts(ok() ? "YES" : "NO");
    }
    return 0;
}

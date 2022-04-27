#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
char s[N];
int a[6][210];
vector<int> id;

bool ok() {
    char *str = "harbin";
    for (int i = 0; i < 6; ++i) {
        if (a[id[i]][str[i]] == 0)
            return false;
    }
    return true;
}

void gao() {
    do {
        if (ok()) {
            puts("Yes");
            return;
        }
    } while (next_permutation(id.begin(), id.end()));
    puts("No");
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        for (int i = 0; i < 6; ++i) {
            a[i]['h'] = 0;
            a[i]['a'] = 0;
            a[i]['r'] = 0;
            a[i]['b'] = 0;
            a[i]['i'] = 0;
            a[i]['n'] = 0;
            scanf("%s", s + 1);
            for (int j = 1, len = strlen(s + 1); j <= len; ++j) {
                a[i][s[j]] = 1;
            }
        }
        id.clear();
        for (int i = 0; i < 6; ++i) id.push_back(i);
        gao();
    }
    return 0;
}

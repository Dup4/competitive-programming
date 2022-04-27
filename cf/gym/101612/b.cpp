#include <bits/stdc++.h>
using namespace std;

#define N 10010
char s[N];
int ge[210], ne[210];

void File() {
    freopen("boolean.in", "r", stdin);
    freopen("boolean.out", "w", stdout);
}
int main() {
    File();
    while (scanf("%s", s + 1) != EOF) {
        memset(ge, 0, sizeof ge);
        memset(ne, 0, sizeof ne);
        for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
            if (isalpha(s[i])) {
                if (i > 1 && s[i - 1] == '~') {
                    ne[s[i]] = 1;
                } else {
                    ge[s[i]] = 1;
                }
            }
        }
        int tot = 0;
        bool flag = 1;
        for (int i = 0; i < 210; ++i) {
            tot += ge[i] || ne[i];
            if (ge[i] && ne[i]) {
                flag = 0;
            }
        }
        printf("%lld\n", (1ll << tot) - flag);
    }
    return 0;
}

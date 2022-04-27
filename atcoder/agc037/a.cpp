#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
char s[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        int res = 1;
        int len = strlen(s + 1);
        int pre = 1;
        for (int i = 2; i <= len;) {
            if (i - pre == 2) {
                pre = i;
                ++i;
            } else {
                if (s[i] == s[pre]) {
                    pre = i;
                    i += 2;
                } else {
                    pre = i;
                    ++i;
                }
            }
            if (i <= len + 1)
                ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}

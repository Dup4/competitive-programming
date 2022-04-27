#include <bits/stdc++.h>
using namespace std;

#define N 110
char s[N];

int main() {
    int T;
    scanf("%d", &T);
    getchar();
    while (T--) {
        int res = 0;
        gets(s);
        for (int i = 0, len = strlen(s); i < len; ++i) {
            if (s[i] == 'a' || s[i] == 'o' || s[i] == 'i' || s[i] == 'e' || s[i] == 'u') {
                ++res;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

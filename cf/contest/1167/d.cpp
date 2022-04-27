#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n;
char s[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        int l = 0, r = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '(') {
                printf("%d", l);
                l ^= 1;
            } else {
                printf("%d", r);
                r ^= 1;
            }
        }
        puts("");
    }
    return 0;
}

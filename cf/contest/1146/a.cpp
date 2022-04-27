#include <bits/stdc++.h>
using namespace std;

#define N 110
char s[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        int cnt = 0;
        int sze = strlen(s + 1);
        for (int i = 1; i <= sze; ++i) {
            cnt += s[i] == 'a';
        }
        for (int i = sze; i >= 1; --i) {
            if (cnt > i / 2) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}

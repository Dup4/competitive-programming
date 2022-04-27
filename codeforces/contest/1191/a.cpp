#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    char *s = "DACB";
    while (scanf("%d", &x) != EOF) {
        int tot = 0;
        char S = 'Z';
        for (int i = 0; i <= 2; ++i) {
            if (s[(x + i) % 4] < S) {
                tot = i;
                S = s[(x + i) % 4];
            }
        }
        printf("%d %c\n", tot, S);
    }
    return 0;
}

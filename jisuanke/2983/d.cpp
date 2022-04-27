#include <bits/stdc++.h>
using namespace std;

#define N 5000010
int k;
char s[N], res[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        scanf("%d", &k);
        int top = 0;
        int len = strlen(s + 1);
        for (int i = 1; i <= len; ++i) {
            while (top > 0 && s[i] < res[top] && len - i + 1 + top > k) {
                --top;
            }
            if (top < k) {
                res[++top] = s[i];
            }
        }
        res[top + 1] = 0;
        printf("%s\n", res + 1);
    }
    return 0;
}

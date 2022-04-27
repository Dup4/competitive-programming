#include <bits/stdc++.h>
using namespace std;

#define N 300010
char s[N];
int n;

void work() {
    for (int i = 2; i <= n; ++i) {
        if (s[i] < s[i - 1]) {
            puts("YES");
            printf("%d %d\n", i - 1, i);
            return;
        }
    }
    puts("NO");
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        work();
    }
    return 0;
}

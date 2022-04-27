#include <bits/stdc++.h>
using namespace std;

#define N 50
char G[N][N];
int n, m;

int main() {
    srand(time(NULL));
    char *s = "LRUD";
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%*s");
        }
        for (int i = 1; i <= 50000; ++i) {
            putchar(s[rand() % 4]);
        }
        puts("");
    }
    return 0;
}

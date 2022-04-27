#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k;

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        int x = (n - k) / 2 + 1;
        for (int i = 1; i <= n; ++i) {
            printf("%c", "10"[i % x == 0]);
        }
        puts("");
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        puts((a[1] == a[n / 2 + 1]) ? "Bob" : "Alice");
    }
    return 0;
}

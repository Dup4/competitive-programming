#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        int mid = n / 2;
        if (a[mid] == a[mid + 1]) {
            puts("0");
        } else {
            printf("%d\n", a[mid + 1] - a[mid]);
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define N 50
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int res = 0;
        for (int i = 2; i < n; ++i) {
            int f = a[i] < a[i - 1];
            int g = a[i] < a[i + 1];
            if (f ^ g) {
                ++res;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

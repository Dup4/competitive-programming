#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n, m, k;

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        int Min = n + m - 1;
        ll tot = 1ll * n * m;
        if (k > tot - Min) {
            puts("-1");
        } else {
            printf("%d\n", n + m - 2);
        }
    }
    return 0;
}

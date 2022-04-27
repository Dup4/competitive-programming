#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n, k;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        ll x = (k == 1 ? n : 1ll * n * n);
        while (x >= 10) {
            int y = 0;
            while (x) {
                y += x % 10;
                x /= 10;
            }
            x = y;
        }
        printf("%lld\n", x);
    }
    return 0;
}

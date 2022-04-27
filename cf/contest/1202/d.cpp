#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
ll n;
ll f(ll x) {
    return x * (x - 1) / 2;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        for (int i = 32000; i >= 2; --i) {
            while (f(i) <= n) {
                n -= f(i);
                putchar('1');
            }
            putchar('3');
        }
        assert(n == 0);
        puts("37");
    }
    return 0;
}

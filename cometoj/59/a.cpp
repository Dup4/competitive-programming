#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, k;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &k, &n);
        if (k == 1) {
            printf("%lld\n", n - 1);
            continue;
        }
        ll base = 1;
        int res = 0;
        ll remind = n - 1;
        for (int i = 1;; ++i) {
            base = base * k;
            if (remind > base) {
                remind -= base;
            } else {
                res = i + i - 1;
                if (remind > base / k) {
                    ++res;
                }
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define db double
#define ull unsigned long long
ull n;
mt19937_64 rd(time(0));

bool check(ull x) {
    if (x < 0)
        return 0;
    if (x == 0)
        return 1;
    ull mid = floor(sqrt(x));
    ull zero = 0;
    for (ull i = max(zero, mid - 10); i <= min(x, mid + 10); ++i) {
        if (i * i == x)
            return 1;
    }
    return 0;
}

int main() {
    while (scanf("%llu", &n) != EOF) {
        set<ull> se;
        ull limit = min(n, 1000000ull);
        for (ull i = 0; i <= limit; ++i) {
            ull j = n - i * i;
            if (check(j)) {
                se.insert(min(i * i, j));
            }
        }
        if (n >= 1000000000000ull) {
            if (check(n) || (n % 2 == 0 && check(n / 2))) {
                puts("1");
                continue;
            }
            for (int i = 1; i <= 5000000; ++i) {
                ull x = rd() % (3000000001) + 1000000;
                ull y = n - x * x;
                if (check(y)) {
                    se.insert(min(x * x, y));
                }
            }
        }
        printf("%d\n", (int)se.size());
    }
    return 0;
}

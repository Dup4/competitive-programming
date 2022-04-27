#include <cstdio>
using namespace std;
int n, y;
long long x, z;

int main() {
    scanf("%d", &n);
    y = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &z);
        if (z != x) {
            if (!y)
                x = z;
            else
                --y;
        } else {
            ++y;
        }
    }
    printf("%lld\n", x);
    return 0;
}

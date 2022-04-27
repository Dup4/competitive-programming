#include <bits/stdc++.h>
using namespace std;
#define random(a, b) (rand() % (b - a + 1) + a)

int main() {
    srand(time(NULL));
    int n = 5000, m = 5000;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", random(0, m - 1), " \n"[i == n]);
    }
    return 0;
}

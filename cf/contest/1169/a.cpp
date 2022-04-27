#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a, x, b, y;

int main() {
    while (scanf("%d%d%d%d%d", &n, &a, &x, &b, &y) != EOF) {
        bool F = (a == b);
        while (a != x && b != y) {
            ++a;
            if (a > n)
                a = 1;
            --b;
            if (b <= 0)
                b = n;
            F |= (a == b);
        }
        puts(F ? "YES" : "NO");
    }
    return 0;
}

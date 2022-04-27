#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 10;
int n, a[N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) a[i] = i;
        ll A = 0;
        do {
            int score = 0;
            for (int i = 2; i <= n; i += 2) {
                if (gcd(a[i - 1], a[i]) == 1)
                    ++score;
            }
            A += score;
        } while (next_permutation(a + 1, a + 1 + n));
        ll B = 1;
        for (int i = 1; i <= n; ++i) B *= i;
        ll g = gcd(A, B);
        A /= g;
        B /= g;
        printf("%d %lld %lld\n", n, A, B);
    }
    return 0;
}

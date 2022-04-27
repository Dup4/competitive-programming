#include <bits/stdc++.h>
using namespace std;

int n, q;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        while (q--) {
            int s, t;
            scanf("%d%d", &s, &t);
            printf("%d\n", min(2, gcd(s, t)));
        }
    }
    return 0;
}

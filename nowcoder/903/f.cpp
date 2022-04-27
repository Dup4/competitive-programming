#include <bits/stdc++.h>
using namespace std;

int main() {
    int s, m, n;
    while (scanf("%d%d%d", &m, &n, &s) != EOF) {
        if (m % (s + 1) == 0 && n <= s) {
            puts("Bob");
        } else {
            puts("Alice");
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}
int main() {
    int n = 5, k = random(1, 15);
    printf("%d %d\n", n, k);
    for (int i = 1; i <= n; ++i) printf("%d%c", random(1, 5), " \n"[i == n]);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
    int n = 100000, m = 100000;
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", rnd() % 2, " \n"[i == n]);
    }
    for (int i = 1; i <= m; ++i) {
        printf("%d %d %d\n", i, rnd() % n + 1, rnd() % 1000000000);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
    int n = 300;
    cout << n << endl;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) printf("%d%c", rnd() % 2, " \n"[j == n]);
    cout << 0 << endl;
}

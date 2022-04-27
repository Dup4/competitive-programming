#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5000, m = 5000;
    cout << n << "\n";
    for (int i = 1; i <= n; ++i) printf("%d%c", (i & 1) + 1, " \n"[i == n]);
    cout << m << "\n";
    for (int i = 1; i <= m; ++i) printf("%d%c", (i & 1) + 1, " \n"[i == m]);
    return 0;
}

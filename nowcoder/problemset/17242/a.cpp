#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int N = 1e5 + 10;
rope<int> ro;
int n, q, a[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) a[i] = i;
        ro.append(a + 1, n);
        for (int i = 1, p, s; i <= q; ++i) {
            scanf("%d%d", &p, &s);
            ro = ro.substr(p - 1, s) + ro.substr(0, p - 1) + ro.substr(p + s - 1, n - p - s + 1);
        }
        for (int i = 0; i < n; ++i) printf("%d%c", ro[i], " \n"[i == n - 1]);
    }
    return 0;
}

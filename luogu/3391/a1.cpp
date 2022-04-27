#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N = 1e5 + 10;
rope<int> A, B, T;
int n, q, a[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        A.clear();
        B.clear();
        for (int i = 1; i <= n; ++i) a[i] = i;
        A = rope<int>(a, a + 1 + n);
        reverse(a + 1, a + 1 + n);
        B = rope<int>(a, a + 1 + n);
        for (int i = 1, l, r; i <= q; ++i) {
            scanf("%d%d", &l, &r);
            T = A.substr(l, r - l + 1);
            A = A.substr(0, (l - 1) + 1) + B.substr(n - r + 1, r - l + 1) + A.substr(r + 1, n - (r + 1) + 1);
            B = B.substr(0, n - r + 1) + T + B.substr(n - l + 2, n - (n - l + 2) + 1);
        }
        for (int i = 1; i <= n; ++i) printf("%d%c", A[i], " \n"[i == n]);
    }
    return 0;
}

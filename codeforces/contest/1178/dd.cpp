#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m, d[N];

bool prime(int x) {
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return 0;
    return 1;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(d, 0, sizeof d);
        assert(prime(m));
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            ++d[u];
            ++d[v];
        }
        for (int i = 1; i <= m; ++i) {
            assert(prime(d[i]));
        }
    }
    return 0;
}

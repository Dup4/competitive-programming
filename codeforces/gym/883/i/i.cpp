#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int n, k, a[N];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int l = 0, r = a[n] - a[1], res = r;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if
    }

    return 0;
}

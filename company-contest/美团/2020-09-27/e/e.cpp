#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 10;
int n, a[N], b[N], que[N << 1];

bool ok() {
    int l = N, r = l - 1;
    int pos = 0;
    for (int i = 1; i <= n; ++i) {
        que[++r] = b[i];
        while (l <= r) {
            if (que[l] == a[pos + 1])
                ++l, ++pos;
            else if (que[r] == a[pos + 1])
                ++pos, --r;
            else
                break;
        }
    }
    return pos == n;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[i] = i;
        }
        puts(ok() ? "Yes" : "No");
    }
    return 0;
}

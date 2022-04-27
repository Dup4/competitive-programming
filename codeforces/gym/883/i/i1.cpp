#include <bits/stdc++.h>
using namespace std;

#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}

const int N = 3e5 + 10;
int n, K, a[N], f[N], S[N];

int ok(int x) {
    // dbg(x);
    memset(f, 0, sizeof f);
    S[0] = 0;
    int l = 1;
    for (int i = 1; i <= n; ++i) {
        while (a[i] - a[l] > x) ++l;
        int r = i - K + 1;
        //	dbg(i, l, r);
        if ((l <= r && (l - 1 <= 0 || S[r - 1] - S[l - 2] > 0)))
            f[i] = 1;
        S[i] = S[i - 1] + f[i];
    }
    return f[n];
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int l = 0, r = a[n] - a[1], res = r;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (ok(mid)) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}

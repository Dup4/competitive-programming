#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], res[N], m, f[N];
bool F;

void gao(int l, int r, int lazy) {
    if (l == r) {
        if (a[l] - lazy != 0) {
            F = 0;
        }
        return;
    }
    if (f[r] <= l) {
        int len = r - l + 1;
        if (len & 1) {
            F = 0;
            return;
        }
        int mid = (l + r) >> 1;
        res[++m] = mid;
        gao(l, mid, lazy + 1);
        gao(mid + 1, r, lazy + 1);
    } else {
        int ql = l, qr = r, pos = l;
        while (qr - ql >= 0) {
            int mid = (ql + qr) >> 1;
            if (f[mid] <= l) {
                pos = mid;
                ql = mid + 1;
            } else {
                qr = mid - 1;
            }
        }
        res[++m] = pos;
        gao(l, pos, lazy + 1);
        gao(pos + 1, r, lazy + 1);
    }
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        m = 0;
        F = 1;
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i] == a[i - 1])
                f[i] = f[i - 1];
            else
                f[i] = i;
        }
        gao(1, n, 0);
        if (!F || m != n - 1)
            puts("Impossible");
        else {
            puts("Possible");
            for (int i = 1; i <= m; ++i) printf("%d%c", res[i], " \n"[i == m]);
        }
    }
    return 0;
}

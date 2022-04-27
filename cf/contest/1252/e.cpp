#include <bits/stdc++.h>
using namespace std;
const int N = 100000 + 10;
int deng[N], len[N], flag[N];
int a[N], b[N], c[N];
int n, l, r, k;

void gao(int p, int x, int y) {
    int z = x - p;
    for (int i = 1; i <= p; ++i) c[i] = 1;
    for (int i = 1; i <= p; ++i) {
        if (z > k - 1) {
            c[i] = k;
            z -= (k - 1);
        } else {
            c[i] += z;
            break;
        }
    }
    if (y == 1) {
        int t;
        for (int i = 1; i <= p / 2; ++i) {
            t = c[i];
            c[i] = c[p - i + 1];
            c[p - i + 1] = t;
        }
    } else {
        for (int i = 1; i <= p; ++i) c[i] *= (-1);
    }
}

int main() {
    scanf("%d%d%d%d", &n, &l, &r, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int d = 0, t = 0;
    flag[0] = -1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] == a[i - 1]) {
            ++d;
            deng[d] = i - d;
        } else if ((a[i] > a[i - 1] && flag[t] == 1) || (a[i] < a[i - 1] && flag[t] == 0)) {
            len[t]++;
        } else {
            ++t;
            if (a[i] > a[i - 1])
                flag[t] = 1;
            else
                flag[t] = 0;
            len[t] = 1;
        }
    }
    if (flag[1] == 1)
        b[1] = l;
    else
        b[1] = l + len[1];
    int j = 1;
    for (int i = 1; i <= t; ++i) {
        int x;
        if (flag[i] == 1) {
            x = len[i];
            if (i < n && b[j] + len[i] - len[i + 1] < l)
                x = l + len[i + 1] - b[j];
            gao(len[i], x, 1);
        } else if (flag[i] == 0) {
            x = b[j] - l;
            gao(len[i], x, 0);
        }
        for (int y = 1; y <= len[i]; ++y) {
            ++j;
            b[j] = b[j - 1] + c[y];
        }
    }
    int f = 0;
    for (int i = 1; i <= j; ++i)
        if (b[i] < l || b[i] > r) {
            f = 1;
            break;
        }
    if (f == 1)
        printf("-1");
    else {
        int y = 1;
        for (int i = 1; i <= j; ++i) {
            printf("%d", b[i]);
            if (y <= d && i == deng[y]) {
                printf(" %d", b[i]);
                ++y;
            }
            if (i != j)
                printf(" ");
        }
    }
    printf("\n");
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
bitset<N> bit[10];
int n, m, s[N], t[N];
ll diff, res;

void del(int x) {
    int now = s[x] - '0';
    if (bit[now][x] == 1)
        --diff;
    else
        ++diff;
    bit[now][x] ^= 1;
}

void init() {
    for (int i = 0; i < 10; ++i) bit[i].reset();
    diff = 0;
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) scanf("%d", s + i);
        for (int i = 1; i <= m; ++i) scanf("%d", t + i);
        diff = m;
        res = 0;
        for (int i = 1; i <= m; ++i) {
            int now = t[i] - '0';
            bit[now][i] = 1;
        }
        for (int i = 1; i <= m; ++i) {
            int now = s[i] - '0';
            if (bit[now][i] == 0)
                ++diff;
            else
                --diff;
            bit[now][i] ^= 1;
        }
        for (int i = m; i <= n; ++i) {
            res += (diff == 0);
            if (i < n) {
                del(i - m + 1);
                add(m);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}

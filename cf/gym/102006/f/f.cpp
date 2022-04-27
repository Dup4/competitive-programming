#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10, INF = 0x3f3f3f3f;
int t, n, cnt[N], f[N], pre[N];
char s[110];

inline void chmin(int &x, int y) {
    if (x > y)
        x = y;
}

int main() {
    freopen("tests.in", "r", stdin);
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &t, &n);
        for (int i = 0; i < (1 << t); ++i) cnt[i] = 0, f[i] = INF, pre[i] = -1;
        f[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            int res = 0;
            for (int j = 0; j < t; ++j) {
                if (s[j] == '1') {
                    res |= 1 << j;
                }
            }
            ++cnt[res];
        }
        for (int j = 0; j < t; ++j) {
            for (int i = 0; i < 1 << t; ++i) {
                if (!(i >> j & 1))
                    cnt[i] += cnt[i ^ (1 << j)];
            }
        }
        for (int i = 0; i < 1 << t; ++i) {
            for (int j = 0; j < t; ++j) {
                if ((i >> j) & 1) {
                    if (f[i ^ (1 << j)] < f[i]) {
                        f[i] = f[i ^ (1 << j)];
                        pre[i] = j;
                    }
                }
            }
            f[i] += cnt[i];
        }
        vector<int> vec;
        int it = (1 << t) - 1;
        while (it) {
            vec.push_back(pre[it]);
            it = it ^ (1 << pre[it]);
        }
        printf("%d\n", f[(1 << t) - 1]);
        reverse(vec.begin(), vec.end());
        for (int i = 0; i < t; ++i) printf("%d%c", vec[i] + 1, " \n"[i == t - 1]);
    }
    return 0;
}

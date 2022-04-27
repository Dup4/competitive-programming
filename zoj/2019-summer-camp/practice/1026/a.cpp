#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
int a[10][N];
vector<int> vec[2];

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

int f(vector<int> &vec) {
    bit.init();
    int res = 0;
    for (auto it : vec) {
        res = (res + bit.query(it + 1, N - 1)) % 2;
        bit.update(it, 1);
    }
    return res;
}

bool ok() {
    vec[0].clear();
    vec[1].clear();
    int cnt[2] = {0, 0};
    for (int j = 1; j <= n; ++j) {
        int x = a[1][j], y = a[2][j], z = a[3][j];
        int xx = (x - 1) / 3, yy = (y - 1) / 3, zz = (z - 1) / 3;
        if (xx != yy || xx != zz)
            return 0;
        if ((y > x && y > z) || (y < x && y < z))
            return 0;
        if (((xx + 1) & 1) ^ (j & 1))
            return 0;
        if (j & 1) {
            vec[0].push_back(xx + 1);
            if (x > z)
                cnt[0] ^= 1;
        } else {
            vec[1].push_back(xx + 1);
            if (x > z)
                cnt[1] ^= 1;
        }
    }
    return (f(vec[0]) == cnt[1] && f(vec[1]) == cnt[0]);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        vec[0].clear();
        vec[1].clear();
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", a[i] + j);
            }
        }
        puts(ok() ? "Yes" : "No");
    }
    return 0;
}

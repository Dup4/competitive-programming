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
const int N = 1e6 + 100, INF = 0x3f3f3f3f;
int n, m, a[N], b[N], sa[4][N], sb[4][N];

inline void chmax(int& x, int y) {
    if (x < y)
        x = y;
}

struct BIT {
    int a[N << 1], n;
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof(a[0]) * (n + 10));
    }
    void update(int x, int v) {
        for (; x > 0; x -= x & -x) chmax(a[x], v);
    }
    int query(int x) {
        int res = -INF;
        for (; x < n; x += x & -x) chmax(res, a[x]);
        return res;
    }
} A, B;

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &m);
        int OFFSET = max(n, m) + 10;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= m; ++i) scanf("%d", b + i);
        a[0] = b[0] = 1;
        a[n + 1] = 3;
        b[m + 1] = 3;
        A.init(OFFSET * 2);
        B.init(OFFSET * 2);
        for (int i = 1; i <= 3; ++i) {
            sa[i][0] = sb[i][0] = 0;
            for (int j = 1; j <= n; ++j) sa[i][j] = sa[i][j - 1] + (a[j] == i);
            for (int j = 1; j <= m; ++j) sb[i][j] = sb[i][j - 1] + (b[j] == i);
            sa[i][n + 1] = sa[i][n];
            sb[i][m + 1] = sb[i][m];
        }
        int res = 0;
        int Max = min(sa[1][n], sb[1][m]);
        int posa = n, posb = m;
        int posa2 = n + 1, posb2 = m + 1;
        int z = -1, Maxz = min(sa[3][n], sb[3][m]);
        for (int i = Max; i >= 0; --i) {
            while (!(sa[1][posa] == i && a[posa] == 1)) {
                --posa;
            }
            while (!(sb[1][posb] == i && b[posb] == 1)) {
                --posb;
            }
            while (z < Maxz) {
                ++z;
                while (!(sa[3][n] - sa[3][posa2 - 1] == z && a[posa2] == 3)) {
                    --posa2;
                }
                while (!(sb[3][m] - sb[3][posb2 - 1] == z && b[posb2] == 3)) {
                    --posb2;
                }
                //	dbg(i, z, posa2, posb2);
                if (posa2 > posa && posb2 > posb) {
                    //		dbg(z, posa, posa2, posb, posb2, z + sb[2][posb2], z + sa[2][posa2]);
                    A.update(sa[2][posa2] - sb[2][posb2] + OFFSET, z + sb[2][posb2]);
                    B.update(sb[2][posb2] - sa[2][posa2] + OFFSET, z + sa[2][posa2]);
                } else {
                    --z;
                    break;
                }
            }
            chmax(res, i + max(A.query(sa[2][posa] - sb[2][posb] + OFFSET) - sb[2][posb],
                                   B.query(sb[2][posb] - sa[2][posa] + OFFSET) - sa[2][posa]));
            // dbg(i, res);
        }
        printf("%d\n", res);
    }
    return 0;
}

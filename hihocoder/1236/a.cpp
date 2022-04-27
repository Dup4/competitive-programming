#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
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
#define fi first
#define se second
const int N = 5e4 + 10, M = 300;
int n, m, q, b[5];
pII a[5][N];

namespace DivideUnit {
int pos[N], posl[N], posr[N], blk;
bitset<N> b[5][M], res, tmp;
void init() {
    blk = (int)sqrt(n);
    for (int i = 1; i <= n; ++i) {
        pos[i] = (i - 1) / blk + 1;
        if (i == 1 || pos[i] != pos[i - 1])
            posl[pos[i]] = i;
        posr[pos[i]] = i;
    }
    for (int i = 0; i < 5; ++i) {
        sort(a[i] + 1, a[i] + 1 + n);
        b[i][0].reset();
        for (int j = 1; j <= n; ++j) {
            if (j == posl[pos[j]]) {
                b[i][pos[j]] = b[i][pos[j] - 1];
            }
            b[i][pos[j]][a[i][j].se] = 1;
        }
    }
}
int query(int c[5]) {
    res.set();
    for (int i = 0; i < 5; ++i) {
        int id = upper_bound(a[i] + 1, a[i] + 1 + n, pII(c[i], n + 1)) - a[i] - 1;
        if (!id)
            return 0;
        tmp = b[i][pos[id] - 1];
        for (int j = posl[pos[id]]; j <= id; ++j) tmp[a[i][j].se] = 1;
        res &= tmp;
    }
    return res.count();
}
}  // namespace DivideUnit

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 5; ++j) {
                scanf("%d", &a[j][i].fi);
                a[j][i].se = i;
            }
        }
        DivideUnit::init();
        scanf("%d", &q);
        int lst = 0;
        for (int i = 1; i <= q; ++i) {
            for (int j = 0; j < 5; ++j) {
                scanf("%d", b + j);
                b[j] ^= lst;
            }
            lst = DivideUnit::query(b);
            printf("%d\n", lst);
        }
    }
    return 0;
}

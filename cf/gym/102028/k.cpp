#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 1e5 + 10;
const int M = 22;
int n, m, q, rt, f[N][M];
char s[N];
struct Hash {
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * 131;
    }
    ull a[N];
    inline void gao(char *s) {
        a[0] = s[0];
        for (int i = 1; s[i]; ++i) {
            a[i] = a[i - 1] * 131 + s[i];
        }
    }
    inline ull get(int l, int r) {
        return a[r] - a[l - 1] * base[r - l + 1];
    }
} hs;
ull Hash::base[N] = {0};
vector<vector<pair<int, char>>> G;
unordered_map<ull, int> mp;
void DFS(int u, ull Hs) {
    mp[Hs] = u;
    for (auto &it : G[u]) DFS(it.first, Hs * 131 + it.second);
}

int main() {
    Hash::init();
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d", &n, &m, &q);
        G.clear();
        G.resize(n + 1);
        mp.clear();
        rt = 0;
        for (int i = 1, fa; i <= n; ++i) {
            char ch;
            scanf("%d %c", &fa, &ch);
            G[fa].emplace_back(i, ch);
        }
        DFS(0, 0);
        scanf("%s", s + 1);
        hs.gao(s);
        for (int i = 1; i <= m; ++i) {
            int l = i, r = m, res = i;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (mp.count(hs.get(i, mid))) {
                    res = mid + 1;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            f[i][0] = res + 1;
        }
        for (int i = 0; i < M; ++i) f[m + 1][i] = f[m + 2][i] = m + 1;
        for (int j = 1; j < M; ++j) {
            for (int i = 1; i <= m; ++i) {
                f[i][j] = f[f[i][j - 1]][j - 1];
            }
        }
        for (int _q = 1, l, r; _q <= q; ++_q) {
            scanf("%d%d", &l, &r);
            int res = 0;
            for (int i = M - 1; i >= 0; --i) {
                if (f[l][i] <= r) {
                    res += (1 << i);
                    l = f[l][i];
                }
            }
            int pos = -1;
            if (mp.count(hs.get(l, r)))
                pos = mp[hs.get(l, r)];
            else
                ++res, pos = 0;
            printf("%d %d\n", res, pos);
        }
    }
    return 0;
}

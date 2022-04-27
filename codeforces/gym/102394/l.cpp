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
    cout << arg << " ";
    err(args...);
}
const int N = 5e3 + 10;
int n, m, q, a[N], vis[N], used[N], b[N], c[N];

bool gao() {
    int sze;
    scanf("%d", &sze);
    for (int i = 1; i <= sze; ++i) scanf("%d", c + i);
    vector<int> vec;
    for (int i = 1; i <= sze; ++i) {
        if (!vis[c[i]])
            vec.push_back(c[i]);
    }
    for (int i = 1; i <= m && i <= sze; ++i) {
        if (b[i] == c[i])
            return true;
    }
    for (int i = m + 1, j = 0, len = vec.size(); i <= sze && j < len; ++i, ++j) {
        if (vec[j] == c[i])
            return true;
    }
    for (int i = m + vec.size(); i <= sze; ++i) {
        if (c[i] == 0)
            return true;
    }
    return false;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &q);
        memset(vis, 0, sizeof(vis[0]) * (n + 5));
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), vis[a[i]] = 1;
        m = 0;
        memset(used, 0, sizeof(used[0]) * (n + 5));
        for (int i = 1; i <= n; ++i) {
            int x = a[i];
            //	dbg(i, x, used[x]);
            if (used[x] == 0) {
                b[++m] = x;
                used[x] = m;
            } else {
                for (int j = used[x]; j <= m; ++j) {
                    b[j] = b[j + 1];
                    used[b[j]] = j;
                }
                b[m] = x;
                used[x] = m;
            }
        }
        reverse(b + 1, b + 1 + m);
        for (int i = 1; i <= m; ++i) printf("%d%c", b[i], " \n"[i == m]);
        while (q--) puts(gao() ? "Yes" : "No");
    }
    return 0;
}

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
#define SZ(x) (int(x.size()))

const int N = 2e5 + 10;
int n, st, ed;
char s[N];

struct UFS {
    int fa[N], rk[N];
    void init(int n) {
        memset(fa, 0, sizeof(fa[0]) * (n + 5));
        memset(rk, 0, sizeof(rk[0]) * (n + 5));
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (rk[fx] > rk[fy])
                swap(fx, fy);
            fa[fx] = fy;
            if (rk[fx] == rk[fy])
                ++rk[fy];
            return true;
        }
        return false;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ufs;

bool ok() {
    ufs.init(n);
    vector<int> vec;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'o')
            vec.push_back(i);
    }
    for (int i = 2; i <= n; ++i)
        if (s[i] == '.' || s[i] == 'o' || s[i] == 's' || s[i] == 'e') {
            if (s[i - 1] == '.' || s[i - 1] == 'o' || s[i - 1] == 's' || s[i - 1] == 'e')
                ufs.merge(i - 1, i);
        }
    for (int i = 1; i < SZ(vec); ++i) ufs.merge(vec[i - 1], vec[i]);
    return !ufs.same(st, ed);
}

int gao1(int st) {
    for (int i = st - 1; i >= 1; --i) {
        if (s[i] == '.') {
            s[i] = '#';
            if (ok())
                return 1;
            s[i] = '.';
            break;
        }
    }
    for (int i = st + 1; i <= n; ++i) {
        if (s[i] == '.') {
            s[i] = '#';
            if (ok())
                return 1;
            s[i] = '.';
            break;
        }
    }
    return 0;
}

int gao2(int st) {
    int i, j;
    for (i = st - 1; i >= 1; --i) {
        if (s[i] == '.') {
            break;
        }
    }
    for (j = st + 1; j <= n; ++j) {
        if (s[j] == '.') {
            break;
        }
    }
    // dbg(st, i, j);
    if (i >= 1 && j <= n) {
        s[i] = '#';
        s[j] = '#';
        if (ok())
            return 1;
        s[i] = '.';
        s[j] = '.';
    }
    return 0;
}

int gao() {
    if (ok())
        return 0;
    if (gao1(st))
        return 1;
    if (gao1(ed))
        return 1;
    if (gao2(st))
        return 2;
    if (gao2(ed))
        return 2;
    return -1;
}

int main() {
    freopen("portals.in", "r", stdin);
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%s", &n, s + 1);
        for (int i = 1; i <= n; ++i) {
            if (s[i] == 's')
                st = i;
            else if (s[i] == 'e')
                ed = i;
        }
        printf("%d\n", gao());
    }
    return 0;
}

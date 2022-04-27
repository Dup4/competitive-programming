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
void err(const T &arg, const Ts &...args) {
    cout << arg << " ";
    err(args...);
}
const int N = 5e3 + 10;
int n, m, q, a[N], vis[N], used[N], b[N], c[N];

struct custom_hash {
    unsigned long long operator()(unsigned long long x) const {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

struct Trie2 {
    struct node {
        unordered_map<int, int, custom_hash> nx;
        node() {
            nx.clear();
        }
    } t[N * N];
    int rt, tot;
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        rt = newnode();
    }
    void insert(int *a) {
        int root = 1;
        for (int i = 1; i <= n; ++i) {
            if (t[root].nx[a[i]] == 0) {
                int tmp = newnode();
                t[root].nx[a[i]] = tmp;
                if (a[i] == 0)
                    return;
            }
            root = t[root].nx[a[i]];
        }
    }
    bool query(int *a) {
        int root = 1;
        for (int i = 1; i <= *a; ++i) {
            if (t[root].nx.count(a[i]) == 0)
                return false;
            root = t[root].nx[a[i]];
            if (a[i] == 0)
                return true;
        }
        return true;
    }
} trie2;

bool gao() {
    scanf("%d", c);
    for (int i = 1; i <= *c; ++i) scanf("%d", c + i);
    return trie2.query(c);
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &q);
        memset(b, 0, sizeof(b[0]) * (n + 5));
        memset(vis, 0, sizeof(vis[0]) * (n + 5));
        trie2.init();
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
            reverse(b + 1, b + 1 + m);
            trie2.insert(b);
            reverse(b + 1, b + 1 + m);
        }
        //	reverse(b + 1, b + 1 + m);
        //	for (int i = 1; i <= m; ++i)
        //		printf("%d%c", b[i], " \n"[i == m]);
        while (q--) puts(gao() ? "Yes" : "No");
    }
    return 0;
}

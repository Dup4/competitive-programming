#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
    cout << arg << ' ';
    err(args...);
}
const int N = 1e6 + 10, ALP = 26, INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
char s[N];
int n;
ll f[N];

struct ACAM {
    struct node {
        int nx[ALP], fail;
        int len, val;
        node() {}
        void init() {
            val = INF;
            len = 0;
        }
    } t[N];
    int root, tot;
    int que[N], ql, qr;
    //节点从1开始
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
        root = 0;
    }
    void insert(char *s, int val) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; s[i]; ++i) {
            if (t[now].nx[s[i] - 'a'] == 0)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
            t[now].len = i + 1;
        }
        t[now].val = min(t[now].val, val);
        t[now].len = len;
    }
    void build() {
        ql = 1, qr = 0;
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i]) {
                t[t[root].nx[i]].fail = 0;
                que[++qr] = t[root].nx[i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            for (int i = 0; i < ALP; ++i) {
                if (t[now].nx[i] == 0) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    que[++qr] = t[now].nx[i];
                }
            }
        }
        vector<int> vec;
        for (int i = 1; i <= tot; ++i) vec.push_back(i);
        sort(vec.begin(), vec.end(), [&](int x, int y) {
            return t[x].len < t[y].len;
        });
        for (auto &it : vec) {
            int &fail = t[it].fail;
            while (fail != root) {
                if (t[fail].val != INF)
                    break;
                fail = t[fail].fail;
            }
        }
    }
    ll query(char *s) {
        int len = strlen(s + 1);
        int now = root;
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for (int i = 1; s[i]; ++i) {
            now = t[now].nx[s[i] - 'a'];
            for (int j = now; j; j = t[j].fail) {
                if (t[j].val != INF) {
                    f[i] = min(f[i], f[i - t[j].len] + t[j].val);
                }
            }
        }
        return f[len] == INFLL ? -1 : f[len];
    }
} acam;

int main() {
    scanf("%d", &n);
    acam.init();
    int tot = 0;
    for (int i = 1, x; i <= n; ++i) {
        scanf("%s%d", s, &x);
        tot += strlen(s);
        acam.insert(s, x);
    }
    // cout << tot << endl;
    acam.build();
    scanf("%s", s + 1);
    printf("%lld\n", acam.query(s));
    return 0;
}

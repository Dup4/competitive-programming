#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10, ALP = 26, INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
char s[N];
int n;

struct ACAM {
    int nx[N][ALP];
    int fail[N];
    int len[N], val[N];
    ll f[N];
    int root, tot;
    int que[N], ql, qr;
    //节点从1开始
    int newnode() {
        ++tot;
        memset(nx[tot], -1, sizeof nx[tot]);
        len[tot] = 0;
        val[tot] = INF;
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    void insert(char *s, int _val) {
        int now = root;
        for (int i = 0; s[i]; ++i) {
            if (nx[now][s[i] - 'a'] == -1)
                nx[now][s[i] - 'a'] = newnode();
            now = nx[now][s[i] - 'a'];
            len[now] = i + 1;
        }
        val[now] = min(val[now], _val);
    }
    void build() {
        ql = 1, qr = 0;
        for (int i = 0; i < ALP; ++i) {
            if (nx[root][i] == -1) {
                nx[root][i] = root;
            } else {
                fail[nx[root][i]] = root;
                que[++qr] = nx[root][i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            for (int i = 0; i < ALP; ++i) {
                if (nx[now][i] == -1) {
                    nx[now][i] = nx[fail[now]][i];
                } else {
                    fail[nx[now][i]] = nx[fail[now]][i];
                    que[++qr] = nx[now][i];
                }
            }
        }
        //剪枝 缩减跳fail过程中的无效点
        vector<int> vec;
        for (int i = 1; i <= tot; ++i) vec.push_back(i);
        sort(vec.begin(), vec.end(), [&](int x, int y) {
            return len[x] < len[y];
        });
        for (auto &it : vec) {
            while (fail[it] != root) {
                if (val[fail[it]] != INF)
                    break;
                fail[it] = fail[fail[it]];
            }
        }
    }
    ll query(char *s) {
        int n = strlen(s + 1);
        int now = root;
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for (int i = 1; i <= n; ++i) {
            now = nx[now][s[i] - 'a'];
            for (int j = now; j != root; j = fail[j]) {
                if (val[j] != INF) {
                    f[i] = min(f[i], f[i - len[j]] + val[j]);
                }
            }
        }
        return f[n] == INFLL ? -1 : f[n];
    }
} acam;

int main() {
    scanf("%d", &n);
    acam.init();
    for (int i = 1, x; i <= n; ++i) {
        scanf("%s%d", s, &x);
        acam.insert(s, x);
    }
    acam.build();
    scanf("%s", s + 1);
    printf("%lld\n", acam.query(s));
    return 0;
}

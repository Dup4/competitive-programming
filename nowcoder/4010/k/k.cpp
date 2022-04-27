#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10, ALP = 26, INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
char s[N];
int n;
ll f[N];

struct ACAM {
    struct node {
        int nx[ALP], val, len;
        node() {}
        void init() {
            memset(nx, -1, sizeof nx);
            val = INF;
            len = 0;
        }
    } t[N];
    int root, tot, fail[N];
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    void insert(char *s, int val) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; s[i]; ++i) {
            if (t[now].nx[s[i] - 'a'] == -1)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
            t[now].len = i + 1;
        }
        t[now].val = min(t[now].val, val);
        t[now].len = len;
    }
    void build() {
        queue<int> que;
        fail[root] = root;
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == -1) {
                t[root].nx[i] = root;
            } else {
                fail[t[root].nx[i]] = root;
                que.push(t[root].nx[i]);
            }
        }
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (int i = 0; i < ALP; ++i) {
                if (t[now].nx[i] == -1) {
                    t[now].nx[i] = t[fail[now]].nx[i];
                } else {
                    fail[t[now].nx[i]] = t[fail[now]].nx[i];
                    que.push(t[now].nx[i]);
                }
            }
        }
        vector<int> vec;
        for (int i = 1; i <= tot; ++i) vec.push_back(i);
        sort(vec.begin(), vec.end(), [&](int x, int y) {
            return t[x].len < t[y].len;
        });
        for (auto &it : vec) {
            while (fail[it] != root) {
                if (t[fail[it]].val != INF)
                    break;
                fail[it] = fail[fail[it]];
            }
        }
    }
    ll query(char *s) {
        int len = strlen(s + 1);
        int now = root;
        for (int i = 1; i <= len; ++i) f[i] = INFLL;
        f[0] = 0;
        for (int i = 1; s[i]; ++i) {
            now = t[now].nx[s[i] - 'a'];
            int tmp = now;
            while (tmp != root) {
                if (t[tmp].val != INF) {
                    f[i] = min(f[i], f[i - t[tmp].len] + t[tmp].val);
                }
                tmp = fail[tmp];
            }
        }
        return f[len] == INFLL ? -1 : f[len];
    }
} acam;

int main() {
    while (scanf("%d", &n) != EOF) {
        acam.init();
        int tot = 0;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%s%d", s, &x);
            tot += strlen(s);
            acam.insert(s, x);
        }
        acam.build();
        scanf("%s", s + 1);
        printf("%lld\n", acam.query(s));
    }
    return 0;
}

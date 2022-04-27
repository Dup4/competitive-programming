#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n;
string s[N], t;
ll f[N], g[N];

#define ALP 26
struct ACAM {
    struct node {
        int nx[ALP], fail;
        int cnt;
        node() {
            memset(nx, -1, sizeof nx);
            cnt = 0;
        }
    } t[N];
    int root, tot;
    int que[N], ql, qr;
    //节点从1开始
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    void insert(string s) {
        int len = s.size();
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (t[now].nx[s[i] - 'a'] == -1)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
        }
        ++t[now].cnt;
    }
    void build() {
        ql = 1, qr = 0;
        t[root].fail = root;
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == -1) {
                t[root].nx[i] = root;
            } else {
                t[t[root].nx[i]].fail = root;
                que[++qr] = t[root].nx[i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            t[now].cnt += t[t[now].fail].cnt;
            for (int i = 0; i < ALP; ++i) {
                if (t[now].nx[i] == -1) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    que[++qr] = t[now].nx[i];
                }
            }
        }
    }
    void query(string s, ll *f) {
        int len = s.size();
        int now = root;
        for (int i = 0; i < len; ++i) {
            now = t[now].nx[s[i] - 'a'];
            f[i] = t[now].cnt;
        }
    }
} ac;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> t) {
        cin >> n;
        ac.init();
        for (int i = 1; i <= n; ++i) cin >> s[i], ac.insert(s[i]);
        ac.build();
        ac.query(t, f);
        ac.init();
        for (int i = 1; i <= n; ++i) {
            reverse(s[i].begin(), s[i].end());
            ac.insert(s[i]);
        }
        ac.build();
        reverse(t.begin(), t.end());
        ac.query(t, g);
        ll res = 0;
        int len = t.size();
        reverse(g, g + len);
        for (int i = 0; i < len - 1; ++i) {
            res += f[i] * g[i + 1];
        }
        cout << res << "\n";
    }
    return 0;
}

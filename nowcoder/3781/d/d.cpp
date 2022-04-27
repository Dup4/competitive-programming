#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int ALP = 26;
char s[N];
int f[N], g[N];

struct PAM {
    struct node {
        int Next[ALP];
        int fail;
        int num, len, cnt, sum;
        void init(int _len = 0) {
            memset(Next, 0, sizeof Next);
            fail = 0;
            num = cnt = sum = 0;
            len = _len;
        }
    } t[N];
    int s[N];
    int last;
    int n;
    int p;
    int Max;

    int newnode(int len) {
        t[p].init(len);
        return p++;
    }
    void init() {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1;
        t[0].fail = 1;
        Max = 0;
    }
    int get_fail(int x) {
        while (s[n - t[x].len - 1] != s[n]) x = t[x].fail;
        return x;
    }
    bool add(int c) {
        bool F = 0;
        c -= 'a';
        s[++n] = c;
        int cur = get_fail(last);
        if (!t[cur].Next[c]) {
            int now = newnode(t[cur].len + 2);
            Max = max(Max, t[cur].len + 2);
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;
            t[now].num = t[t[now].fail].num + 1;
            t[now].sum = t[t[now].fail].sum + t[now].len;
            F = 1;
        }
        last = t[cur].Next[c];
        ++t[last].cnt;
        return F;
    }
} pam;

int main() {
    while (scanf("%s", s + 1) != EOF) {
        int n = strlen(s + 1);
        pam.init();
        f[0] = 0;
        for (int i = 1; s[i]; ++i) {
            pam.add(s[i]);
            f[i] = pam.Max;
        }
        g[n + 1] = 0;
        pam.init();
        for (int i = n; i >= 1; --i) {
            pam.add(s[i]);
            g[i] = pam.Max;
        }
        int res = 0;
        for (int i = 1; s[i]; ++i) {
            if (f[i] && g[i + 1]) {
                res = max(res, f[i] + g[i + 1]);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

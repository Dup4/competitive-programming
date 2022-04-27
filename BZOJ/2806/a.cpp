#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 2;
int n, q, pre[N], f[N], que[N], head, tail;
char s[N];

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, fa, nx[ALP];
        node() {
            maxlen = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst;
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id) {
        int cur = newnode(), p;
        t[cur].maxlen = t[lst].maxlen + 1;
        for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
        if (!p) {
            t[cur].fa = 1;
        } else {
            int q = t[p].nx[id];
            if (t[q].maxlen == t[p].maxlen + 1) {
                t[cur].fa = q;
            } else {
                int clone = newnode();
                t[clone] = t[q];
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    void gao(char *s) {
        for (int i = 1, now = 1, len = 0; s[i]; ++i) {
            int c = s[i] - '0';
            while (now && !t[now].nx[c]) {
                now = t[now].fa;
                len = t[now].maxlen;
            }
            if (!now) {
                now = 1;
                len = 0;
            } else {
                now = t[now].nx[c];
                ++len;
            }
            pre[i] = len;
        }
    }
} sam;
bool check(int k) {
    int len = strlen(s + 1);
    f[0] = 0;
    head = 1;
    tail = 0;
    for (int i = 1; s[i]; ++i) {
        f[i] = f[i - 1];
        if (i - k >= 0) {
            while (head <= tail && f[que[tail]] - que[tail] <= f[i - k] - i + k) --tail;
            que[++tail] = i - k;
        }
        while (head <= tail && que[head] < i - pre[i]) ++head;
        if (head <= tail)
            f[i] = max(f[i], f[que[head]] + i - que[head]);
    }
    return f[len] * 10 >= len * 9;
}

int main() {
    while (scanf("%d%d", &q, &n) != EOF) {
        sam.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            sam.lst = 1;
            for (int j = 0; s[j]; ++j) sam.extend(s[j] - '0');
        }
        for (int i = 1; i <= q; ++i) {
            scanf("%s", s + 1);
            sam.gao(s);
            int l = 1, r = strlen(s + 1), res = 0;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (check(mid)) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}

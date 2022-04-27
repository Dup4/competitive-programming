#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 26;
const int INF = 0x3f3f3f3f;
int n, m;
char s[N], t[N];

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    // pos表示那个结点在字符串的endpos的最小值，即firstpos
    struct node {
        int maxlen, pos, fa, nx[ALP];
        node() {
            maxlen = pos = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst, c[N << 1], rk[N << 1];
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id, int _pos) {
        int cur = newnode(), p;
        t[cur].pos = _pos;
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
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a', i + 1);
        }
        memset(c, 0, sizeof c);
        for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
        for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
        for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
        for (int i = tot; i; --i) {
            int cur = rk[i], fa = t[cur].fa;
            t[fa].pos = min(t[fa].pos, t[cur].pos);
        }
    }
    int gao(char *s) {
        int res = -1;
        for (int i = 0, now = 1; s[i]; ++i) {
            int p = INF, c = s[i] - 'a';
            for (int j = c + 1; j < 26; ++j) {
                if (t[now].nx[j]) {
                    p = min(p, t[t[now].nx[j]].pos);
                    break;
                }
            }
            if (p != INF) {
                res = max(res, i + n - p + 1);
            }
            if (!t[now].nx[c])
                break;
            now = t[now].nx[c];
        }
        return res;
    }
} sam;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        scanf("%s%s", s, t);
        sam.build(s);
        printf("%d\n", sam.gao(t));
    }
    return 0;
}

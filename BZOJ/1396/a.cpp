#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
const int ALP = 26;
const int INF = 1e9;
int n;
char s[N];

struct SEG {
    struct node {
        int Min;
        node() {
            Min = INF;
        }
        void add(int x) {
            Min = min(Min, x);
        }
    } t[N << 2];
    void down(int id) {
        int &lazy = t[id].Min;
        t[id << 1].add(lazy);
        t[id << 1 | 1].add(lazy);
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
        if (l >= ql && r <= qr) {
            t[id].add(x);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
    }
    int query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].Min;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg[2];

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
    int tot, lst, d[N << 1];
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
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a');
        }
        memset(d, 0, sizeof d);
        for (int i = 1; i <= tot; ++i) ++d[t[i].fa];
    }
    void gao() {
        seg[0].build(1, 1, n);
        seg[1].build(1, 1, n);
        for (int i = 1; i <= tot; ++i)
            if (!d[i]) {
                int r = t[i].maxlen, l = r - t[t[i].fa].maxlen;
                seg[0].update(1, 1, n, 1, l, r + 1);
                seg[1].update(1, 1, n, l + 1, r, r - l + 1);
            }
    }
} sam;

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        sam.build(s + 1);
        sam.gao();
        for (int i = 1; i <= n; ++i) printf("%d\n", min(seg[0].query(1, 1, n, i) - i, seg[1].query(1, 1, n, i)));
    }
    return 0;
}

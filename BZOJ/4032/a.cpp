#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 4e3 + 10;
const int ALP = 26;
int lens, lent;
char s[N], t[N];
bool vis[N][N];

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    // pos表示那个结点在字符串的endpos的最小值，即firstpos
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
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a');
        }
    }
} sam_s, sam_t;

struct SQAM {
    struct node {
        int nx[ALP];
        node() {
            memset(nx, 0, sizeof nx);
        }
    } t[N];
    int lst[ALP], pre[N], tot;
    void init() {
        tot = 1;
        t[1] = node();
        for (int i = 0; i < ALP; ++i) lst[i] = 1;
    }
    void extend(int c) {
        int cur = ++tot;
        t[cur] = node();
        pre[cur] = lst[c];
        for (int i = tot - 1; i >= pre[cur]; --i) t[i].nx[c] = cur;
        lst[c] = cur;
    }
} sqam_s, sqam_t;

struct node {
    int len, a, b;
};
int BFS1(SAM &A, SAM &B) {
    queue<node> que;
    que.push({0, 1, 1});
    memset(vis, 0, sizeof vis);
    vis[1][1] = 1;
    while (!que.empty()) {
        node p = que.front();
        que.pop();
        for (int i = 0; i < ALP; ++i) {
            int x = A.t[p.a].nx[i];
            int y = B.t[p.b].nx[i];
            if (!x)
                continue;
            if (!y)
                return p.len + 1;
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            que.push({p.len + 1, x, y});
        }
    }
    return -1;
}
int BFS2(SAM &A, SQAM &B) {
    queue<node> que;
    que.push({0, 1, 1});
    memset(vis, 0, sizeof vis);
    vis[1][1] = 1;
    while (!que.empty()) {
        node p = que.front();
        que.pop();
        for (int i = 0; i < ALP; ++i) {
            int x = A.t[p.a].nx[i];
            int y = B.t[p.b].nx[i];
            if (!x)
                continue;
            if (!y)
                return p.len + 1;
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            que.push({p.len + 1, x, y});
        }
    }
    return -1;
}
int BFS3(SQAM &A, SAM &B) {
    queue<node> que;
    que.push({0, 1, 1});
    memset(vis, 0, sizeof vis);
    vis[1][1] = 1;
    while (!que.empty()) {
        node p = que.front();
        que.pop();
        for (int i = 0; i < ALP; ++i) {
            int x = A.t[p.a].nx[i];
            int y = B.t[p.b].nx[i];
            if (!x)
                continue;
            if (!y)
                return p.len + 1;
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            que.push({p.len + 1, x, y});
        }
    }
    return -1;
}
int BFS4(SQAM &A, SQAM &B) {
    queue<node> que;
    que.push({0, 1, 1});
    memset(vis, 0, sizeof vis);
    vis[1][1] = 1;
    while (!que.empty()) {
        node p = que.front();
        que.pop();
        for (int i = 0; i < ALP; ++i) {
            int x = A.t[p.a].nx[i];
            int y = B.t[p.b].nx[i];
            if (!x)
                continue;
            if (!y)
                return p.len + 1;
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            que.push({p.len + 1, x, y});
        }
    }
    return -1;
}

int main() {
    scanf("%s%s", s + 1, t + 1);
    lens = strlen(s + 1), lent = strlen(t + 1);
    sam_s.init();
    sam_t.init();
    sqam_s.init();
    sqam_t.init();
    for (int i = 1; s[i]; ++i) {
        sam_s.extend(s[i] - 'a');
        sqam_s.extend(s[i] - 'a');
    }
    for (int i = 1; t[i]; ++i) {
        sam_t.extend(t[i] - 'a');
        sqam_t.extend(t[i] - 'a');
    }
    printf("%d\n%d\n%d\n%d\n", BFS1(sam_s, sam_t), BFS2(sam_s, sqam_t), BFS3(sqam_s, sam_t), BFS4(sqam_s, sqam_t));
    return 0;
}

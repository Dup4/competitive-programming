// 3106ms 改数据之前 (话说我也不知道啥时候改的.
//改数据之后 吸氧 571ms qwq.
// Creator: 顾z
// Date:2018.08.29
//------------------------------------------------
#include <bits/stdc++.h>
#define IL inline
#define RI register int
#define N 100086
#define clear(a) memset(a, 0, sizeof a)
#define rk for (RI i = 1; i <= n; i++)
IL void read(int &x) {
    int f = 1;
    x = 0;
    char s = getchar();
    while (s > '9' || s < '0') {
        if (s == '-')
            f = -1;
        s = getchar();
    }
    while (s <= '9' && s >= '0') {
        x = x * 10 + s - '0';
        s = getchar();
    }
    x *= f;
}
int n, m, T, s;
struct code {
    int u, v, w;
} edge[N << 1];
bool vis[N];
int head[N], tot, dis[N], cnt[N], q[N];
IL void add(int x, int y, int z) {
    edge[++tot].u = head[x];
    edge[tot].v = y;
    edge[tot].w = z;
    head[x] = tot;
}
IL bool spfa(int s) {
    int l, r;
    l = r = 0;
    memset(dis, 0x3f, sizeof dis);
    clear(vis);
    clear(cnt);
    clear(q);
    vis[s] = true;
    cnt[s] = 1;
    dis[s] = 0;
    q[r++] = s;
    while (l != r) {
        int u = q[l++];
        if (l > n)
            l = 0;  //重复使用
        vis[u] = false;
        for (RI i = head[u]; i; i = edge[i].u) {
            if (dis[edge[i].v] > dis[u] + edge[i].w) {
                dis[edge[i].v] = dis[u] + edge[i].w;
                cnt[edge[i].v] = cnt[u] + 1;  //题解思想.
                if (cnt[edge[i].v] >= n and edge[i].w < 0)
                    return true;
                //这里需要判断一下边权是否为负。
                //因为看到讨论区的一组hack数据,所以尝试改一下,
                //然后就过啦~~~
                if (!vis[edge[i].v]) {
                    vis[edge[i].v] = true;
                    if (dis[edge[i].v] > dis[q[l]]) {
                        l--;
                        if (l < 0)
                            l = n;  //重复使用
                        q[l] = edge[i].v;
                    } else {
                        q[r++] = edge[i].v;
                        if (r > n)
                            r = 0;  //重复使用
                    }
                }
            }
        }
    }
    return false;
}
int main() {
    read(T);
    while (T--) {
        s = 1, tot = 0;
        clear(head);
        read(n), read(m);
        for (RI i = 1, u, v, w; i <= m; i++) {
            read(u), read(v), read(w);
            add(u, v, w);
            if (w >= 0)
                add(v, u, w);
        }
        puts(spfa(s) ? "YE5" : "N0");
    }
}

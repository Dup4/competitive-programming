#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define MAX 700000
#define lson (t[x].ch[0])
#define rson (t[x].ch[1])
#define rg register
inline int read() {
    rg int x = 0, t = 1;
    rg char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-')
        t = -1, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
    return x * t;
}
struct Node {
    int ch[2], ff;
    int rev;
    int sum, ma, v, r;
} t[MAX];
int S[MAX], top, n, m;
void pushup(int x) {
    t[x].sum = t[lson].sum + t[rson].sum + t[x].v;
    t[x].ma = (t[t[lson].ma].r > t[t[rson].ma].r) ? t[rson].ma : t[lson].ma;
    if (t[x].r < t[t[x].ma].r)
        t[x].ma = x;
}
inline bool isroot(int x) {
    return t[t[x].ff].ch[0] != x && t[t[x].ff].ch[1] != x;
}
inline void rotate(int x) {
    rg int y = t[x].ff, z = t[y].ff;
    rg int k = t[y].ch[1] == x;
    if (!isroot(y))
        t[z].ch[t[z].ch[1] == y] = x;
    t[x].ff = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    t[t[x].ch[k ^ 1]].ff = y;
    t[x].ch[k ^ 1] = y;
    t[y].ff = x;
    pushup(y);
    pushup(x);
}
inline void pushdown(int x) {
    if (!t[x].rev)
        return;
    t[lson].rev ^= 1;
    t[rson].rev ^= 1;
    t[x].rev ^= 1;
    swap(lson, rson);
}
void Splay(int x) {
    S[top = 1] = x;
    for (int i = x; !isroot(i); i = t[i].ff) S[++top] = t[i].ff;
    while (top) pushdown(S[top--]);
    while (!isroot(x)) {
        int y = t[x].ff, z = t[y].ff;
        if (!isroot(y))
            (t[y].ch[1] == x) ^ (t[z].ch[1] == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
}
void access(int x) {
    for (int y = 0; x; y = x, x = t[x].ff) Splay(x), t[x].ch[1] = y, pushup(x);
}
void makeroot(int x) {
    access(x);
    Splay(x);
    t[x].rev ^= 1;
}
void split(int x, int y) {
    makeroot(x);
    access(y);
    Splay(y);
}
void link(int x, int y) {
    makeroot(x);
    t[x].ff = y;
}
void cut(int x, int y) {
    split(x, y);
    t[x].ff = t[y].ch[0] = 0;
    pushup(y);
}
int findroot(int x) {
    access(x);
    Splay(x);
    while (lson) x = lson;
    return x;
}
int main() {
    n = read();
    m = read();
    for (rg int i = 0; i <= n; ++i) t[i].r = 1e9;
    rg char ch[10];
    while (m--) {
        scanf("%s", ch);
        if (ch[0] == 'f') {
            rg int id = read() + 1, u = read() + 1, v = read() + 1, tmp = read(), len = read();
            t[id + n].r = tmp;
            t[id + n].v = len;
            if (findroot(u) != findroot(v))
                link(u, id + n), link(v, id + n);  //未联通
            else {
                split(u, v);
                if (t[t[v].ma].r < tmp) {
                    rg int ss = t[v].ma;
                    cut(u, ss);
                    cut(v, ss);
                    link(u, id + n);
                    link(v, id + n);
                }
            }
        } else if (ch[0] == 'm') {
            rg int u = read() + 1, v = read() + 1;
            if (findroot(u) != findroot(v))
                puts("-1");
            else
                split(u, v), printf("%d %d\n", t[t[v].ma].r, t[v].sum);
        } else {
            rg int id = read() + 1, len = read();
            makeroot(id + n);
            t[id + n].v = len;
            pushup(id + n);
        }
    }
    return 0;
}

// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC optimize(2)
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include <bitset>
#include <assert.h>
#include <time.h>
#include <iomanip>
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
// char buf[(1 << 21) + 1], * p1 = buf, * p2 = buf;
// #define int long long
#define lowbit(x) (x & (-x))
#define lson root << 1, l, mid
#define rson root << 1 | 1, mid + 1, r
#define pb push_back
typedef unsigned long long ull;
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::vector<ll> VI;
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define SZ(x) ((int)((x).size()))
#define bug puts("BUG")
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-6;
template <class T>
inline void read(T &x)
{
    int sign = 1;char c = getchar();x = 0;
    while (c > '9' || c < '0'){if (c == '-')sign = -1;c = getchar();}
    while (c >= '0' && c <= '9'){x = x * 10 + c - '0';c = getchar();}
    x *= sign;
}
#ifdef LOCAL
    FILE* _INPUT=freopen("input.txt", "r", stdin);
    // FILE* _OUTPUT=freopen("output.txt", "w", stdout);
#endif
using namespace std;
const int maxn = 5e4 + 10;
const int maxm = 5e4 + 10;
struct NODE{
    int val, ls, rs;
    void clear()
    {
        val = ls = rs = 0;
    }
} node[maxn * 50];
int rt[maxn * 2], tot;
int a[maxn * 2], sorted[maxn * 2];
int n, m, M;
inline void pushup(int root)
{
    node[root].val = node[node[root].ls].val + node[node[root].rs].val;
}

void update(int &root, int l, int r, int a, int v)
{
    if(!root)
    {
//		assert(tot < maxn * 52);
        root = ++tot;
        node[root].clear();
    }
    if (l == r)
    {
        node[root].val += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (a <= sorted[mid])
    {
        update(node[root].ls, l, mid, a, v);
    }else
    {
        update(node[root].rs, mid + 1, r, a, v);
    }
    pushup(root);
}

void upd(int k, int v)
{
    for (int i = k; i <= n; i += lowbit(i))
        update(rt[i], 1, M, a[k], v);
}
int lq[maxm], rq[maxm], ltsz, rtsz;
void init(int l, int r)
{
    --l;
    ltsz = rtsz = 0;
    for (; l; l -= lowbit(l))
        lq[ltsz++] = rt[l];
    for (; r; r -= lowbit(r))
        rq[rtsz++] = rt[r];
    // assert(ltsz <= 30 && rtsz <= 30);
}

int sum()
{
    int res = 0;
    for (int i = 0; i < rtsz; ++i)
        res += node[node[rq[i]].ls].val;
    for (int i = 0; i < ltsz; ++i)
        res -= node[node[lq[i]].ls].val;
    return res;
}

int query(int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    int cur = sum();
    if (cur >= k)
    {
        for (int i = 0; i < rtsz; ++i)
            rq[i] = node[rq[i]].ls;
        for (int i = 0; i < ltsz; ++i)
            lq[i] = node[lq[i]].ls;
        return query(l, mid, k);
    }else
    {
        for (int i = 0; i < rtsz; ++i)
            rq[i] = node[rq[i]].rs;
        for (int i = 0; i < ltsz; ++i)
            lq[i] = node[lq[i]].rs;
        return query(mid + 1, r, k - cur);
    }
}

int slove(int l, int r, int k)
{
    init(l, r);
    return sorted[query(1, M, k)];
}

struct que{
    int l, r, v;
    que(int v = 0, int l = 0, int r = -1) : v(v), l(l), r(r) {}
} opt[maxm];

int main()
{
    int t = 1;
    for (; t--;)
    {
        M = 0;
        tot = 0;
        read(n), read(m);
        for (int i = 1; i <= n; ++i)
        {
            read(a[i]);
            sorted[++M] = a[i];
        }
        char c;
        int l, r, v;
        for (int i = 0; i < m;++i)
        {
            scanf(" %c", &c);
            if(c=='Q')
            {
                read(l), read(r), read(v);
                opt[i] = que(v, l, r);
            }else
            {
                read(l), read(v);
                opt[i] = que(v, l);
                sorted[++M] = v;
            }
        }
        sort(sorted + 1, sorted + 1 + M);
        M = unique(sorted + 1, sorted + 1 + M) - sorted - 1;
        for (int i = 1; i <= n; ++i)
        {
            upd(i, 1);
        }
        for (int i = 0; i < m; ++i)
        {
            if (opt[i].r == -1)
            {
                upd(opt[i].l, -1);
                a[opt[i].l] = opt[i].v;
                upd(opt[i].l, 1);
            }else
            {
                printf("%d\n", slove(opt[i].l, opt[i].r, opt[i].v));
            }   
        }
        for (int i = 0; i <= n; ++i)
            rt[i] = 0;
        for (int i = 0; i <= tot; ++i)
            node[i].clear();
    }
}

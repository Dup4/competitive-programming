#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, w[N];
char s[N];
struct DA {
    //求SA数组需要用到的中间变量，不需要赋值
    int t1[N], t2[N], c[N];
    int sa[N];
    int Rank[N];
    int height[N];
    //待排序的字符串放在str数组中，从str[0] - s[n - 1]长度为n, 最大值小于m
    int str[N];
    int n, m;
    void init(char *s, int m, int n) {
        this->m = m;
        this->n = n;
        for (int i = 0; i < n; ++i) str[i] = s[i];
        str[n] = 0;
    }
    bool cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    void work() {
        ++n;
        int i, j, p, *x = t1, *y = t2;
        //第一轮基数排序，如果s的最大值很大，可改为快速排序
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[i] = str[i]]++;
        for (i = 1; i < m; ++i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            //直接利用sa数组排序第二关键字
            //后面的j个数第二关键字为空的最小
            for (i = n - j; i < n; ++i) {
                y[p++] = i;
            }
            for (i = 0; i < n; ++i)
                if (sa[i] >= j)
                    y[p++] = sa[i] - j;
            //这样数组y保存的就是按照第二关键字排序的结果
            //基数排序第一关键字
            for (i = 0; i < m; ++i) c[i] = 0;
            for (i = 0; i < n; ++i) c[x[y[i]]]++;
            for (i = 1; i < m; ++i) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            //根据sa和x数组计算新的x数组
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; ++i) {
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
            }
            if (p >= n)
                break;
            //下次基数排序的最大值
            m = p;
        }
        int k = 0;
        --n;
        for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
        // build height
        for (i = 0; i < n; ++i) {
            if (k)
                --k;
            j = sa[Rank[i] - 1];
            while (str[i + k] == str[j + k]) ++k;
            height[Rank[i]] = k;
        }
    }
} da;

template <class T>
void chmax(T &x, T y) {
    if (x < y)
        x = y;
}
template <class T>
void chmin(T &x, T y) {
    if (x > y)
        x = y;
}
// f[] 表示方案数 g[]表示最值
ll f[N], g[N];
struct UF {
    struct node {
        int fa, Max, Min, sze;
        ll M;
        node() {}
        node(int fa, int Max, int Min) : fa(fa), Max(Max), Min(Min) {
            sze = 1;
            M = -1e18;
        }
    } t[N];
    void init(int n, int *w) {
        for (int i = 0; i <= n; ++i) {
            t[i] = node(i, w[i], w[i]);
        }
    }
    int find(int x) {
        return t[x].fa == x ? t[x].fa : t[x].fa = find(t[x].fa);
    }
    void merge(int x, int y, int len) {
        int fx = find(x), fy = find(y);
        f[len] += 1ll * t[fx].sze * t[fy].sze;
        t[fx].fa = fy;
        t[fy].sze += t[fx].sze;
        chmax(t[fy].M, t[fx].M);
        chmax(t[fy].M, max(1ll * t[fx].Max * t[fy].Min, 1ll * t[fx].Min * t[fy].Min));
        chmax(t[fy].M, max(1ll * t[fx].Max * t[fy].Max, 1ll * t[fx].Min * t[fy].Max));
        chmax(t[fy].Max, t[fx].Max);
        chmin(t[fy].Min, t[fx].Min);
        chmax(g[len], t[fy].M);
    }
} uf;

bool cmp(int x, int y) {
    return da.height[x] > da.height[y];
}
int ord[N];
int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s);
        for (int i = 0; i < n; ++i) {
            scanf("%d", w + i);
        }
        for (int i = 0; i <= n + 1; ++i) {
            f[i] = 0;
            g[i] = -1e18;
        }
        da.init(s, 220, n);
        da.work();
        uf.init(n, w);
        for (int i = 1; i <= n; ++i) ord[i] = i + 1;
        sort(ord + 1, ord + n, cmp);
        for (int i = 1; i < n; ++i) {
            uf.merge(da.sa[ord[i]], da.sa[ord[i] - 1], da.height[ord[i]]);
        }
        for (int i = n; i >= 0; --i) {
            f[i] += f[i + 1];
            chmax(g[i], g[i + 1]);
        }
        for (int i = 0; i < n; ++i) {
            printf("%lld %lld\n", f[i], (!f[i] ? 0 : g[i]));
        }
    }
    return 0;
}

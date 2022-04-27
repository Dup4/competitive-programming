#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 10;
const int M = 25;
const int INF = 0x3f3f3f3f;
int _T, n, a[N], b[N], c[N], sta[N], fa[N];
ll dis[N];
struct DA {
    int t1[N], t2[N], c[N];
    int sa[N];
    int Rank[N];
    int height[N];
    int str[N], n, m;
    void init(int *s, int m, int n) {
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
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[i] = str[i]]++;
        for (i = 1; i < m; ++i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            for (i = n - j; i < n; ++i) y[p++] = i;
            for (i = 0; i < n; ++i)
                if (sa[i] >= j)
                    y[p++] = sa[i] - j;
            for (i = 0; i < m; ++i) c[i] = 0;
            for (i = 0; i < n; ++i) c[x[y[i]]]++;
            for (i = 1; i < m; ++i) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; ++i) {
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
            }
            if (p >= n)
                break;
            m = p;
        }
        int k = 0;
        --n;
        for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
        for (i = 0; i < n; ++i) {
            if (k)
                --k;
            j = sa[Rank[i] - 1];
            while (str[i + k] == str[j + k]) ++k;
            height[Rank[i]] = k;
        }
    }
} da;

using pII = pair<int, int>;
#define fi first
#define se second
struct RMQ {
    pII Max[N][M];
    int mm[N];
    void init(int n, int *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = pII(b[i], i);
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    pII query(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
} rmq;

int main() {
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", a + i), b[i + 1] = a[i], c[i + 1] = a[i];
        b[n + 1] = INF;
        rmq.init(n, b);
        *c = n;
        sort(c + 1, c + 1 + n);
        *c = unique(c + 1, c + 1 + n) - c - 1;
        for (int i = 0; i < n; ++i) a[i] = lower_bound(c + 1, c + 1 + *c, a[i]) - c;
        da.init(a, *c + 1, n);
        da.work();
        *sta = 0;
        sta[++*sta] = n + 1;
        dis[n + 1] = 0;
        fa[n + 1] = n + 1;
        for (int i = n; i >= 1; --i) {
            while (*sta && b[i] > b[sta[*sta]]) --*sta;
            fa[i] = sta[*sta];
            dis[i] = 1ll * b[i] * (sta[*sta] - i) + dis[fa[i]];
            //	cout << i << " " << dis[i] << endl;
            sta[++*sta] = i;
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            //	cout << i << " " << da.height[i] << endl;
            int st = da.sa[i] + 1, nx = st, pos = st;
            if (i > 1)
                nx = st + da.height[i];
            if (st != nx) {
                pII tmp = rmq.query(st, nx - 1);
                pos = tmp.se;
            }
            //	cout << st << " " << pos << endl;
            int npos = fa[pos];
            res += 1ll * b[pos] * (npos - nx) + dis[npos];
        }
        printf("%lld\n", res);
    }
    return 0;
}

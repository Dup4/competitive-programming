#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500005;
const int INF = 1e9;

template <typename T>
void read(T &x) {
    x = 0;
    int f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}
template <typename T>
void write(T x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T>
void writeln(T x) {
    write(x);
    puts("");
}

struct Mininfo {
    int Min, Nin, Cnt, Delta;
};
struct Maxinfo {
    int Max, Nax, Cnt, Delta;
};
Mininfo operator+(Mininfo a, Mininfo b) {
    Mininfo ans;
    ans.Cnt = ans.Delta = 0;
    ans.Min = min(a.Min, b.Min);
    ans.Nin = min(a.Nin, b.Nin);
    if (a.Min != ans.Min)
        ans.Nin = min(ans.Nin, a.Min);
    else
        ans.Cnt += a.Cnt;
    if (b.Min != ans.Min)
        ans.Nin = min(ans.Nin, b.Min);
    else
        ans.Cnt += b.Cnt;
    return ans;
}
Maxinfo operator+(Maxinfo a, Maxinfo b) {
    Maxinfo ans;
    ans.Cnt = ans.Delta = 0;
    ans.Max = max(a.Max, b.Max);
    ans.Nax = max(a.Nax, b.Nax);
    if (a.Max != ans.Max)
        ans.Nax = max(ans.Nax, a.Max);
    else
        ans.Cnt += a.Cnt;
    if (b.Max != ans.Max)
        ans.Nax = max(ans.Nax, b.Max);
    else
        ans.Cnt += b.Cnt;
    return ans;
}

struct SEG {
    struct Node {
        int lc, rc, tag;
        ll sum, len;
        Mininfo Min;
        Maxinfo Max;
    } a[N * 2];
    int n, root, size, val[N];
    void update(int root) {
        a[root].sum = a[a[root].lc].sum + a[a[root].rc].sum;
        a[root].Min = a[a[root].lc].Min + a[a[root].rc].Min;
        a[root].Max = a[a[root].lc].Max + a[a[root].rc].Max;
    }
    void build(int &root, int l, int r) {
        root = ++size;
        a[root].len = r - l + 1;
        if (l == r) {
            a[root].sum = val[l];
            a[root].Min = (Mininfo){val[l], INF, 1, 0};
            a[root].Max = (Maxinfo){val[l], -INF, 1, 0};
            return;
        }
        int mid = (l + r) / 2;
        build(a[root].lc, l, mid);
        build(a[root].rc, mid + 1, r);
        update(root);
    }
    void init(int x) {
        n = x;
        root = size = 0;
        build(root, 1, n);
    }
    void addmax(int root, ll val) {
        if (a[root].Max.Max == a[root].Min.Min) {
            a[root].Max.Max += val;
            a[root].Min.Min += val;
            a[root].tag += val;
            a[root].sum += a[root].len * val;
            return;
        }
        if (a[root].Max.Max == a[root].Min.Nin) {
            a[root].Max.Max += val;
            a[root].Max.Delta += val;
            a[root].Min.Nin += val;
            a[root].sum += a[root].Max.Cnt * val;
            return;
        }
        a[root].Max.Max += val;
        a[root].Max.Delta += val;
        a[root].sum += a[root].Max.Cnt * val;
    }
    void addmin(int root, ll val) {
        if (a[root].Min.Min == a[root].Max.Max) {
            a[root].Min.Min += val;
            a[root].Max.Max += val;
            a[root].tag += val;
            a[root].sum += a[root].len * val;
            return;
        }
        if (a[root].Min.Min == a[root].Max.Nax) {
            a[root].Min.Min += val;
            a[root].Min.Delta += val;
            a[root].Max.Nax += val;
            a[root].sum += a[root].Min.Cnt * val;
            return;
        }
        a[root].Min.Min += val;
        a[root].Min.Delta += val;
        a[root].sum += a[root].Min.Cnt * val;
    }
    void pushdown(int root) {
        if (a[root].lc == 0)
            return;
        if (a[root].Max.Delta) {
            ll tmp = a[root].Max.Delta;
            int lc = a[root].lc, rc = a[root].rc;
            if (a[lc].Max.Max == a[rc].Max.Max) {
                addmax(lc, tmp);
                addmax(rc, tmp);
            } else if (a[lc].Max.Max > a[rc].Max.Max)
                addmax(lc, tmp);
            else
                addmax(rc, tmp);
            a[root].Max.Delta = 0;
        }
        if (a[root].Min.Delta) {
            ll tmp = a[root].Min.Delta;
            int lc = a[root].lc, rc = a[root].rc;
            if (a[lc].Min.Min == a[rc].Min.Min) {
                addmin(lc, tmp);
                addmin(rc, tmp);
            } else if (a[lc].Min.Min < a[rc].Min.Min)
                addmin(lc, tmp);
            else
                addmin(rc, tmp);
            a[root].Min.Delta = 0;
        }
        if (a[root].tag) {
            ll tmp = a[root].tag;
            int ch = a[root].lc;
            a[ch].Min.Min += tmp;
            a[ch].Min.Nin += tmp;
            a[ch].Max.Max += tmp;
            a[ch].Max.Nax += tmp;
            a[ch].tag += tmp;
            a[ch].sum += tmp * a[ch].len;
            ch = a[root].rc;
            a[ch].Min.Min += tmp;
            a[ch].Min.Nin += tmp;
            a[ch].Max.Max += tmp;
            a[ch].Max.Nax += tmp;
            a[ch].tag += tmp;
            a[ch].sum += tmp * a[ch].len;
            a[root].tag = 0;
        }
    }
    void add(int root, int l, int r, int ql, int qr, int val) {
        if (l == ql && r == qr) {
            a[root].Min.Min += val;
            a[root].Min.Nin += val;
            a[root].Max.Max += val;
            a[root].Max.Nax += val;
            a[root].tag += val;
            a[root].sum += val * a[root].len;
            return;
        }
        pushdown(root);
        int mid = (l + r) / 2;
        if (mid >= ql)
            add(a[root].lc, l, mid, ql, min(qr, mid), val);
        if (mid + 1 <= qr)
            add(a[root].rc, mid + 1, r, max(mid + 1, ql), qr, val);
        update(root);
    }
    void add(int l, int r, int val) {
        add(root, 1, n, l, r, val);
    }
    void chkmax(int root, int l, int r, int val) {
        if (a[root].Min.Min >= val)
            return;
        if (a[root].Min.Nin > val) {
            addmin(root, val - a[root].Min.Min);
            return;
        }
        int mid = (l + r) / 2;
        pushdown(root);
        chkmax(a[root].lc, l, mid, val);
        chkmax(a[root].rc, mid + 1, r, val);
        update(root);
    }
    void chkmax(int root, int l, int r, int ql, int qr, int val) {
        if (l == ql && r == qr) {
            chkmax(root, l, r, val);
            return;
        }
        pushdown(root);
        int mid = (l + r) / 2;
        if (mid >= ql)
            chkmax(a[root].lc, l, mid, ql, min(qr, mid), val);
        if (mid + 1 <= qr)
            chkmax(a[root].rc, mid + 1, r, max(mid + 1, ql), qr, val);
        update(root);
    }
    void chkmax(int l, int r, int val) {
        chkmax(root, 1, n, l, r, val);
    }
    void chkmin(int root, int l, int r, int val) {
        if (a[root].Max.Max <= val)
            return;
        if (a[root].Max.Nax < val) {
            addmax(root, val - a[root].Max.Max);
            return;
        }
        int mid = (l + r) / 2;
        pushdown(root);
        chkmin(a[root].lc, l, mid, val);
        chkmin(a[root].rc, mid + 1, r, val);
        update(root);
    }
    void chkmin(int root, int l, int r, int ql, int qr, int val) {
        if (l == ql && r == qr) {
            chkmin(root, l, r, val);
            return;
        }
        pushdown(root);
        int mid = (l + r) / 2;
        if (mid >= ql)
            chkmin(a[root].lc, l, mid, ql, min(qr, mid), val);
        if (mid + 1 <= qr)
            chkmin(a[root].rc, mid + 1, r, max(mid + 1, ql), qr, val);
        update(root);
    }
    void chkmin(int l, int r, int val) {
        chkmin(root, 1, n, l, r, val);
    }
    ll sum(int root, int l, int r, int ql, int qr) {
        if (l == ql && r == qr)
            return a[root].sum;
        pushdown(root);
        int mid = (l + r) / 2;
        ll ans = 0;
        if (mid >= ql)
            ans += sum(a[root].lc, l, mid, ql, min(qr, mid));
        if (mid + 1 <= qr)
            ans += sum(a[root].rc, mid + 1, r, max(mid + 1, ql), qr);
        return ans;
    }
    ll sum(int l, int r) {
        return sum(root, 1, n, l, r);
    }
    ll Max(int root, int l, int r, int ql, int qr) {
        if (l == ql && r == qr)
            return a[root].Max.Max;
        pushdown(root);
        int mid = (l + r) / 2;
        ll ans = -INF;
        if (mid >= ql)
            ans = max(ans, Max(a[root].lc, l, mid, ql, min(qr, mid)));
        if (mid + 1 <= qr)
            ans = max(ans, Max(a[root].rc, mid + 1, r, max(mid + 1, ql), qr));
        return ans;
    }
    ll Max(int l, int r) {
        return Max(root, 1, n, l, r);
    }
    ll Min(int root, int l, int r, int ql, int qr) {
        if (l == ql && r == qr)
            return a[root].Min.Min;
        pushdown(root);
        int mid = (l + r) / 2;
        ll ans = INF;
        if (mid >= ql)
            ans = min(ans, Min(a[root].lc, l, mid, ql, min(qr, mid)));
        if (mid + 1 <= qr)
            ans = min(ans, Min(a[root].rc, mid + 1, r, max(mid + 1, ql), qr));
        return ans;
    }
    ll Min(int l, int r) {
        return Min(root, 1, n, l, r);
    }
} seg;

int main() {
    int n, m;
    read(n);
    for (int i = 1; i <= n; i++) read(seg.val[i]);
    seg.init(n);
    read(m);
    for (int i = 1; i <= m; i++) {
        int opt, l, r, val;
        read(opt), read(l), read(r);
        if (opt <= 3)
            read(val);
        if (opt == 1)
            seg.add(l, r, val);
        if (opt == 2)
            seg.chkmax(l, r, val);
        if (opt == 3)
            seg.chkmin(l, r, val);
        if (opt == 4)
            writeln(seg.sum(l, r));
        if (opt == 5)
            writeln(seg.Max(l, r));
        if (opt == 6)
            writeln(seg.Min(l, r));
    }
    return 0;
}

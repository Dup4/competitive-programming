#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
typedef long long ll;
const int N = 5e5 + 10, INF = 0x3f3f3f3f;
int n, q, a[N];

namespace IO {
const int S = (1 << 20) + 5;
// Input Correlation
char buf[S], *H, *T;
inline char gc() {
    if (H == T)
        T = (H = buf) + fread(buf, 1, S, stdin);
    return H == T ? ' ' : *H++;
}
inline bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
template <class T>
inline void read(T &x) {
    register double tmp = 1;
    register bool sign = 0;
    x = 0;
    register char ch = gc();
    for (; !isdigit(ch); ch = gc())
        if (ch == '-')
            sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
        for (ch = gc(); isdigit(ch); ch = gc()) tmp /= 10.0, x += tmp * (ch - '0');
    if (sign)
        x = -x;
}
inline void read(char *s) {
    register char ch = gc();
    for (; blank(ch); ch = gc())
        ;
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
}
// Output Correlation
char obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[110];
int qr;
inline void flush() {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
}
inline void putc(char x) {
    *oS++ = x;
    if (oS == oT)
        flush();
}
template <class I>
inline void write(I x) {
    if (!x)
        putc('0');
    if (x < 0)
        putc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putc(qu[qr--]);
}
template <class I>
inline void writeln(I x) {
    write(x);
    putc('\n');
}
inline void writes(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) putc(s[i]);
    putc('\n');
}
inline void writed(int d, double x) {
    long long t = (long long)floor(x);
    write(t);
    putc('.');
    x -= t;
    while (d--) {
        double y = x * 10;
        x *= 10;
        int c = (int)floor(y);
        putc(c + '0');
        x -= floor(y);
    }
}
}  // namespace IO

struct FHQ {
#define ls(o) t[o].son[0]
#define rs(o) t[o].son[1]
    struct MStack {
        int tot;
        vector<int> vec;
        void init() {
            vec.clear();
            tot = 0;
        }
        int get() {
            int tar = 0;
            if (!vec.empty()) {
                tar = vec.back();
                vec.pop_back();
            } else {
                tar = ++tot;
            }
            return tar;
        }
        void save(int x) {
            vec.push_back(x);
        }
    } mStack;
    struct node {
        int son[2], rnd, sze;
        int val, sum, preMax, sufMax, allMax, modify_tag, rev_tag;
        void init(int _val) {
            son[0] = son[1] = 0;
            sze = 1;
            sum = preMax = sufMax = allMax = val = _val;
            modify_tag = INF;
            rev_tag = 0;
        }
        node() {}
        node(int val) {
            init(val);
        }
        void up_modify(int _modify_tag) {
            val = _modify_tag;
            modify_tag = _modify_tag;
            sum = _modify_tag * sze;
            preMax = sufMax = allMax = max(val, sum);
        }
        void up_rev() {
            swap(son[0], son[1]);
            rev_tag ^= 1;
            swap(preMax, sufMax);
        }
    } t[N * 4];
    int random() {
        static int seed = 703;
        return seed = int(seed * 482147ll % 2147483647);
    }
    int rt;
    void init() {
        mStack.init();
        rt = 0;
        t[0].preMax = t[0].sufMax = t[0].allMax = -INF;
    }
    int newnode(int val) {
        int tmp = mStack.get();
        t[tmp].init(val);
        t[tmp].rnd = random();
        return tmp;
    }
    void pushup(int o) {
        t[o].sze = t[ls(o)].sze + t[rs(o)].sze + 1;
        t[o].sum = t[ls(o)].sum + t[rs(o)].sum + t[o].val;
        t[o].preMax = max(t[ls(o)].preMax, t[ls(o)].sum + t[o].val);
        t[o].preMax = max(t[o].preMax, t[ls(o)].sum + t[o].val + t[rs(o)].preMax);
        t[o].sufMax = max(t[rs(o)].sufMax, t[o].val + t[rs(o)].sum);
        t[o].sufMax = max(t[o].sufMax, t[ls(o)].sufMax + t[o].val + t[rs(o)].sum);
        t[o].allMax = t[o].val;
        t[o].allMax = max(t[o].allMax, t[ls(o)].allMax);
        t[o].allMax = max(t[o].allMax, t[rs(o)].allMax);
        t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].val);
        t[o].allMax = max(t[o].allMax, t[o].val + t[rs(o)].preMax);
        t[o].allMax = max(t[o].allMax, t[ls(o)].sufMax + t[o].val + t[rs(o)].preMax);
    }
    void pushdown(int o) {
        int &modify_tag = t[o].modify_tag;
        int &rev_tag = t[o].rev_tag;
        if (ls(o)) {
            if (modify_tag != INF)
                t[ls(o)].up_modify(modify_tag);
            if (rev_tag)
                t[ls(o)].up_rev();
        }
        if (rs(o)) {
            if (modify_tag != INF)
                t[rs(o)].up_modify(modify_tag);
            if (rev_tag)
                t[rs(o)].up_rev();
        }
        modify_tag = INF;
        rev_tag = 0;
    }
    int build(int l, int r) {
        if (l > r)
            return 0;
        int mid = (l + r) >> 1, val = a[mid];
        int o = newnode(val);
        ls(o) = build(l, mid - 1);
        rs(o) = build(mid + 1, r);
        pushup(o);
        return o;
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd) {
            pushdown(x);
            rs(x) = merge(rs(x), y);
            pushup(x);
            return x;
        } else {
            pushdown(y);
            ls(y) = merge(x, ls(y));
            pushup(y);
            return y;
        }
    }
    //根据sze分 前k个数在以x为根的Treap中，后面的数在以y为根的Treap中
    void split(int now, int k, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            pushdown(now);
            if (k <= t[ls(now)].sze) {
                y = now;
                split(ls(now), k, x, ls(now));
            } else {
                x = now;
                split(rs(now), k - t[ls(now)].sze - 1, rs(now), y);
            }
            pushup(now);
        }
    }
    //在第id个位置插入val
    void insert(int id, int val) {
        int a, b;
        split(rt, id - 1, a, b);
        int c = newnode(val);
        rt = merge(merge(a, c), b);
    }
    void del(int id) {
        int a, b, c;
        split(rt, id - 1, a, b);
        split(b, 1, b, c);
        mStack.save(b);
        rt = merge(a, c);
    }
    void modify(int id, int val) {
        int a, b, c;
        split(rt, id - 1, a, b);
        split(b, 1, b, c);
        t[b].init(val);
        rt = merge(a, merge(b, c));
    }
    void update_modify(int l, int r, int val) {
        int a, b, c;
        split(rt, l - 1, a, b);
        split(b, r - l + 1, b, c);
        t[b].up_modify(val);
        rt = merge(a, merge(b, c));
    }
    void update_rev(int l, int r) {
        int a, b, c;
        split(rt, l - 1, a, b);
        split(b, r - l + 1, b, c);
        t[b].up_rev();
        rt = merge(a, merge(b, c));
    }
    node query(int l, int r) {
        int a, b, c;
        split(rt, l - 1, a, b);
        split(b, r - l + 1, b, c);
        node res = t[b];
        rt = merge(a, merge(b, c));
        return res;
    }
    void print(int x) {
        if (!x)
            return;
        pushdown(x);
        print(ls(x));
        printf("%d %d %d %d %d %d %d\n", x, t[x].val, t[x].son[0], t[x].son[1], t[x].preMax, t[x].sufMax, t[x].allMax);
        print(rs(x));
    }
} fhq;

int main() {
    IO::read(n);
    IO::read(q);
    for (int i = 1; i <= n; ++i) IO::read(a[i]);
    fhq.init();
    fhq.rt = fhq.build(1, n);
    while (q--) {
        static char op[20];
        IO::read(op);
        if (strcmp(op, "INSERT") == 0) {
            static int pos, tot;
            IO::read(pos);
            IO::read(tot);
            for (int i = 1, x; i <= tot; ++i) {
                IO::read(x);
                fhq.insert(pos + i, x);
            }
        } else if (strcmp(op, "DELETE") == 0) {
            static int pos, tot;
            IO::read(pos);
            IO::read(tot);
            for (int i = 0; i < tot; ++i) fhq.del(pos);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            static int pos, tot, c;
            IO::read(pos);
            IO::read(tot);
            IO::read(c);
            fhq.update_modify(pos, pos + tot - 1, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            static int pos, tot;
            IO::read(pos);
            IO::read(tot);
            fhq.update_rev(pos, pos + tot - 1);
        } else if (strcmp(op, "GET-SUM") == 0) {
            static int pos, tot;
            static FHQ::node ans;
            IO::read(pos);
            IO::read(tot);
            ans = fhq.query(pos, pos + tot - 1);
            printf("%d\n", ans.sum);
        } else if (strcmp(op, "MAX-SUM") == 0) {
            static int ans;
            ans = fhq.t[fhq.rt].allMax;
            printf("%d\n", ans);
        }
    }
    return 0;
}

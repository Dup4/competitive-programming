#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, p, q, b[N];

namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 100000
#define ll long long
// fread->read
bool IOerror = 0;
inline char nc() {
    static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
    if (p1 == pend) {
        p1 = buf;
        pend = buf + fread(buf, 1, BUF_SIZE, stdin);
        if (pend == p1) {
            IOerror = 1;
            return -1;
        }
        //{printf("IO error!\n");system("pause");for (;;);exit(0);}
    }
    return *p1++;
}
inline bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
inline void read(int &x) {
    bool sign = 0;
    char ch = nc();
    x = 0;
    for (; blank(ch); ch = nc())
        ;
    if (IOerror)
        return;
    if (ch == '-')
        sign = 1, ch = nc();
    for (; ch >= '0' && ch <= '9'; ch = nc()) x = x * 10 + ch - '0';
    if (sign)
        x = -x;
}
inline void read(ll &x) {
    bool sign = 0;
    char ch = nc();
    x = 0;
    for (; blank(ch); ch = nc())
        ;
    if (IOerror)
        return;
    if (ch == '-')
        sign = 1, ch = nc();
    for (; ch >= '0' && ch <= '9'; ch = nc()) x = x * 10 + ch - '0';
    if (sign)
        x = -x;
}
inline void read(double &x) {
    bool sign = 0;
    char ch = nc();
    x = 0;
    for (; blank(ch); ch = nc())
        ;
    if (IOerror)
        return;
    if (ch == '-')
        sign = 1, ch = nc();
    for (; ch >= '0' && ch <= '9'; ch = nc()) x = x * 10 + ch - '0';
    if (ch == '.') {
        double tmp = 1;
        ch = nc();
        for (; ch >= '0' && ch <= '9'; ch = nc()) tmp /= 10.0, x += tmp * (ch - '0');
    }
    if (sign)
        x = -x;
}
inline void read(char *s) {
    char ch = nc();
    for (; blank(ch); ch = nc())
        ;
    if (IOerror)
        return;
    for (; !blank(ch) && !IOerror; ch = nc()) *s++ = ch;
    *s = 0;
}
inline void read(char &c) {
    for (c = nc(); blank(c); c = nc())
        ;
    if (IOerror) {
        c = -1;
        return;
    }
}
// getchar->read
inline void read1(int &x) {
    char ch;
    int bo = 0;
    x = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar())
        if (ch == '-')
            bo = 1;
    for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - '0', ch = getchar())
        ;
    if (bo)
        x = -x;
}
inline void read1(ll &x) {
    char ch;
    int bo = 0;
    x = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar())
        if (ch == '-')
            bo = 1;
    for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - '0', ch = getchar())
        ;
    if (bo)
        x = -x;
}
inline void read1(double &x) {
    char ch;
    int bo = 0;
    x = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar())
        if (ch == '-')
            bo = 1;
    for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - '0', ch = getchar())
        ;
    if (ch == '.') {
        double tmp = 1;
        for (ch = getchar(); ch >= '0' && ch <= '9'; tmp /= 10.0, x += tmp * (ch - '0'), ch = getchar())
            ;
    }
    if (bo)
        x = -x;
}
inline void read1(char *s) {
    char ch = getchar();
    for (; blank(ch); ch = getchar())
        ;
    for (; !blank(ch); ch = getchar()) *s++ = ch;
    *s = 0;
}
inline void read1(char &c) {
    for (c = getchar(); blank(c); c = getchar())
        ;
}
// scanf->read
inline void read2(int &x) {
    scanf("%d", &x);
}
inline void read2(ll &x) {
#ifdef _WIN32
    scanf("%I64d", &x);
#else
#ifdef __linux
    scanf("%lld", &x);
#else
    puts("error:can't recognize the system!");
#endif
#endif
}
inline void read2(double &x) {
    scanf("%lf", &x);
}
inline void read2(char *s) {
    scanf("%s", s);
}
inline void read2(char &c) {
    scanf(" %c", &c);
}
//    inline void readln2(char *s){gets(s);}
// fwrite->write
struct Ostream_fwrite {
    char *buf, *p1, *pend;
    Ostream_fwrite() {
        buf = new char[BUF_SIZE];
        p1 = buf;
        pend = buf + BUF_SIZE;
    }
    void out(char ch) {
        if (p1 == pend) {
            fwrite(buf, 1, BUF_SIZE, stdout);
            p1 = buf;
        }
        *p1++ = ch;
    }
    void print(int x) {
        static char s[15], *s1;
        s1 = s;
        if (!x)
            *s1++ = '0';
        if (x < 0)
            out('-'), x = -x;
        while (x) *s1++ = x % 10 + '0', x /= 10;
        while (s1-- != s) out(*s1);
    }
    void println(int x) {
        static char s[15], *s1;
        s1 = s;
        if (!x)
            *s1++ = '0';
        if (x < 0)
            out('-'), x = -x;
        while (x) *s1++ = x % 10 + '0', x /= 10;
        while (s1-- != s) out(*s1);
        out('\n');
    }
    void print(ll x) {
        static char s[25], *s1;
        s1 = s;
        if (!x)
            *s1++ = '0';
        if (x < 0)
            out('-'), x = -x;
        while (x) *s1++ = x % 10 + '0', x /= 10;
        while (s1-- != s) out(*s1);
    }
    void println(ll x) {
        static char s[25], *s1;
        s1 = s;
        if (!x)
            *s1++ = '0';
        if (x < 0)
            out('-'), x = -x;
        while (x) *s1++ = x % 10 + '0', x /= 10;
        while (s1-- != s) out(*s1);
        out('\n');
    }
    void print(double x, int y) {
        static ll mul[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000LL,
                100000000000LL, 1000000000000LL, 10000000000000LL, 100000000000000LL, 1000000000000000LL,
                10000000000000000LL, 100000000000000000LL};
        if (x < -1e-12)
            out('-'), x = -x;
        x *= mul[y];
        ll x1 = (ll)floor(x);
        if (x - floor(x) >= 0.5)
            ++x1;
        ll x2 = x1 / mul[y], x3 = x1 - x2 * mul[y];
        print(x2);
        if (y > 0) {
            out('.');
            for (size_t i = 1; i < y && x3 * mul[i] < mul[y]; out('0'), ++i)
                ;
            print(x3);
        }
    }
    void println(double x, int y) {
        print(x, y);
        out('\n');
    }
    void print(char *s) {
        while (*s) out(*s++);
    }
    void println(char *s) {
        while (*s) out(*s++);
        out('\n');
    }
    void flush() {
        if (p1 != buf) {
            fwrite(buf, 1, p1 - buf, stdout);
            p1 = buf;
        }
    }
    ~Ostream_fwrite() {
        flush();
    }
} Ostream;
inline void print(int x) {
    Ostream.print(x);
}
inline void println(int x) {
    Ostream.println(x);
}
inline void print(char x) {
    Ostream.out(x);
}
inline void println(char x) {
    Ostream.out(x);
    Ostream.out('\n');
}
inline void print(ll x) {
    Ostream.print(x);
}
inline void println(ll x) {
    Ostream.println(x);
}
inline void print(double x, int y) {
    Ostream.print(x, y);
}
inline void println(double x, int y) {
    Ostream.println(x, y);
}
inline void print(char *s) {
    Ostream.print(s);
}
inline void println(char *s) {
    Ostream.println(s);
}
inline void println() {
    Ostream.out('\n');
}
inline void flush() {
    Ostream.flush();
}
// puts->write
char Out[OUT_SIZE], *o = Out;
inline void print1(int x) {
    static char buf[15];
    char *p1 = buf;
    if (!x)
        *p1++ = '0';
    if (x < 0)
        *o++ = '-', x = -x;
    while (x) *p1++ = x % 10 + '0', x /= 10;
    while (p1-- != buf) *o++ = *p1;
}
inline void println1(int x) {
    print1(x);
    *o++ = '\n';
}
inline void print1(ll x) {
    static char buf[25];
    char *p1 = buf;
    if (!x)
        *p1++ = '0';
    if (x < 0)
        *o++ = '-', x = -x;
    while (x) *p1++ = x % 10 + '0', x /= 10;
    while (p1-- != buf) *o++ = *p1;
}
inline void println1(ll x) {
    print1(x);
    *o++ = '\n';
}
inline void print1(char c) {
    *o++ = c;
}
inline void println1(char c) {
    *o++ = c;
    *o++ = '\n';
}
inline void print1(char *s) {
    while (*s) *o++ = *s++;
}
inline void println1(char *s) {
    print1(s);
    *o++ = '\n';
}
inline void println1() {
    *o++ = '\n';
}
inline void flush1() {
    if (o != Out) {
        if (*(o - 1) == '\n')
            *--o = 0;
        puts(Out);
    }
}
struct puts_write {
    ~puts_write() {
        flush1();
    }
} _puts;
inline void print2(int x) {
    printf("%d", x);
}
inline void println2(int x) {
    printf("%d\n", x);
}
inline void print2(char x) {
    printf("%c", x);
}
inline void println2(char x) {
    printf("%c\n", x);
}
inline void print2(ll x) {
#ifdef _WIN32
    printf("%I64d", x);
#else
#ifdef __linux
    printf("%lld", x);
#else
    puts("error:can't recognize the system!");
#endif
#endif
}
inline void println2(ll x) {
    print2(x);
    printf("\n");
}
inline void println2() {
    printf("\n");
}
#undef ll
#undef OUT_SIZE
#undef BUF_SIZE
};  // namespace fastIO
using namespace fastIO;

template <class SqrtTreeItem>
class SqrtTree {
private:
    int n, lg, indexSz;
    vector<SqrtTreeItem> v;
    vector<int> clz, layers, onLayer;
    vector<vector<SqrtTreeItem> > pref, suf, between;
    //修改两数运算法则
    inline SqrtTreeItem op(const SqrtTreeItem &a, const SqrtTreeItem &b) {
        return 1ll * a * b % p;
    }

    //`	inline int log2Up(ll x) {
    //`	    while (__builtin_popcountll(x) > 1) {
    //`	        x ^= (x & -x);
    //`	    }
    //`	    return __builtin_ffsll(x);
    //`	}

    inline int log2Up(int n) {
        int res = 0;
        while ((1 << res) < n) {
            res++;
        }
        return res;
    }

    inline void buildBlock(int layer, int l, int r) {
        pref[layer][l] = v[l];
        for (int i = l + 1; i < r; i++) {
            pref[layer][i] = op(pref[layer][i - 1], v[i]);
        }
        suf[layer][r - 1] = v[r - 1];
        for (int i = r - 2; i >= l; i--) {
            suf[layer][i] = op(v[i], suf[layer][i + 1]);
        }
    }

    inline void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
        int bSzLog = (layers[layer] + 1) >> 1;
        int bCntLog = layers[layer] >> 1;
        int bSz = 1 << bSzLog;
        int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
        for (int i = 0; i < bCnt; i++) {
            SqrtTreeItem ans;
            for (int j = i; j < bCnt; j++) {
                SqrtTreeItem add = suf[layer][lBound + (j << bSzLog)];
                ans = (i == j) ? add : op(ans, add);
                between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
            }
        }
    }

    inline void buildBetweenZero() {
        int bSzLog = (lg + 1) >> 1;
        for (int i = 0; i < indexSz; i++) {
            v[n + i] = suf[0][i << bSzLog];
        }
        build(1, n, n + indexSz, (1 << lg) - n);
    }

    inline void updateBetweenZero(int bid) {
        int bSzLog = (lg + 1) >> 1;
        v[n + bid] = suf[0][bid << bSzLog];
        update(1, n, n + indexSz, (1 << lg) - n, n + bid);
    }

    inline void build(int layer, int lBound, int rBound, int betweenOffs) {
        if (layer >= (int)layers.size()) {
            return;
        }
        int bSz = 1 << ((layers[layer] + 1) >> 1);
        for (int l = lBound; l < rBound; l += bSz) {
            int r = min(l + bSz, rBound);
            buildBlock(layer, l, r);
            build(layer + 1, l, r, betweenOffs);
        }
        if (layer == 0) {
            buildBetweenZero();
        } else {
            buildBetween(layer, lBound, rBound, betweenOffs);
        }
    }

    inline void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
        if (layer >= (int)layers.size()) {
            return;
        }
        int bSzLog = (layers[layer] + 1) >> 1;
        int bSz = 1 << bSzLog;
        int blockIdx = (x - lBound) >> bSzLog;
        int l = lBound + (blockIdx << bSzLog);
        int r = min(l + bSz, rBound);
        buildBlock(layer, l, r);
        if (layer == 0) {
            updateBetweenZero(blockIdx);
        } else {
            buildBetween(layer, lBound, rBound, betweenOffs);
        }
        update(layer + 1, l, r, betweenOffs, x);
    }

    inline SqrtTreeItem query(int l, int r, int betweenOffs, int base) {
        if (l == r) {
            return v[l];
        }
        if (l + 1 == r) {
            return op(v[l], v[r]);
        }
        int layer = onLayer[clz[(l - base) ^ (r - base)]];
        int bSzLog = (layers[layer] + 1) >> 1;
        int bCntLog = layers[layer] >> 1;
        int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
        int lBlock = ((l - lBound) >> bSzLog) + 1;
        int rBlock = ((r - lBound) >> bSzLog) - 1;
        SqrtTreeItem ans = suf[layer][l];
        if (lBlock <= rBlock) {
            SqrtTreeItem add = (layer == 0) ? (query(n + lBlock, n + rBlock, (1 << lg) - n, n))
                                            : (between[layer - 1][betweenOffs + lBound + (lBlock << bCntLog) + rBlock]);
            ans = op(ans, add);
        }
        ans = op(ans, pref[layer][r]);
        return ans;
    }

public:
    inline SqrtTreeItem query(int l, int r) {
        return query(l, r, 0, 0);
    }

    inline void update(int x, const SqrtTreeItem &item) {
        v[x] = item;
        update(0, 0, n, 0, x);
    }

    //下标从0开始
    SqrtTree(const vector<SqrtTreeItem> &a) : n((int)a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg + 1) {
        clz[0] = 0;
        for (int i = 1; i < (int)clz.size(); i++) {
            clz[i] = clz[i >> 1] + 1;
        }
        int tlg = lg;
        while (tlg > 1) {
            onLayer[tlg] = (int)layers.size();
            layers.push_back(tlg);
            tlg = (tlg + 1) >> 1;
        }
        for (int i = lg - 1; i >= 0; i--) {
            onLayer[i] = max(onLayer[i], onLayer[i + 1]);
        }
        int betweenLayers = max(0, (int)layers.size() - 1);
        int bSzLog = (lg + 1) >> 1;
        int bSz = 1 << bSzLog;
        indexSz = (n + bSz - 1) >> bSzLog;
        v.resize(n + indexSz);
        pref.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
        suf.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
        between.assign(betweenLayers, vector<SqrtTreeItem>((1 << lg) + bSz));
        build(0, 0, n, 0);
    }
};

int main() {
    int _T;
    read(_T);
    while (_T--) {
        read(n);
        read(p);
        read(q);
        vector<int> a(n);
        for (int i = 0, x; i < n; ++i) {
            read(x);
            a[i] = x;
        }
        SqrtTree<int> sqrtTree(a);
        m = (q / 64) + 2;
        for (int i = 0; i < m; ++i) read(b[i]);
        int lst = 0;
        for (int i = 0, l = 0, r = 0; i < q; ++i) {
            if (i % 64 == 0) {
                l = (b[i / 64] + lst) % n;
                r = (b[i / 64 + 1] + lst) % n;
            } else {
                l = (l + lst) % n;
                r = (r + lst) % n;
            }
            if (l > r)
                swap(l, r);
            if (l == r)
                lst = a[l];
            else
                lst = sqrtTree.query(l, r);
            lst = (lst + 1) % p;
        }
        printf("%d\n", lst);
    }
    return 0;
}

#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
}
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
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 4e5 + 10;
int n, a[N], cnt[32];

namespace IO {
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
inline void readln2(char *s) {
    gets(s);
}
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
};  // namespace IO

struct Trie {
    struct node {
        int son[2], cnt;
        node() {
            son[0] = son[1] = cnt = 0;
        }
    } t[N * 30];
    int rt, tot;
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        rt = newnode();
    }
    void insert(int x, int Max) {
        int root = rt;
        for (int i = Max; i >= 0; --i) {
            int now = (x >> i) & 1;
            if (!t[root].son[now])
                t[root].son[now] = newnode();
            root = t[root].son[now];
            ++t[root].cnt;
        }
    }
    void del(int x, int Max) {
        int root = rt;
        for (int i = Max; i >= 0; --i) {
            int now = (x >> i) & 1;
            root = t[root].son[now];
            --t[root].cnt;
        }
    }
    int query(int x, int Max) {
        int root = rt;
        int res = 0;
        for (int i = Max; i >= 0; --i) {
            int now = (x >> i) & 1;
            if (i < Max) {
                if (t[root].son[now] && now)
                    res += t[t[root].son[now]].cnt;
                now ^= 1;
            }
            root = t[root].son[now];
        }
        root = rt;
        for (int i = Max; i >= 0; --i) {
            int now = (x >> i) & 1;
            if (i < Max) {
                if (t[root].son[now] && !now)
                    res += t[t[root].son[now]].cnt;
            }
            now ^= 1;
            root = t[root].son[now];
        }
        return res & 1;
    }
} trie;

void run() {
    IO::read(n);
    for (int i = 1; i <= n; ++i) IO::read(a[i]), a[i] <<= 1;
    memset(cnt, 0, sizeof cnt);
    for (int Max = 25; Max >= 1; --Max) {
        trie.init();
        trie.insert(a[n], Max);
        for (int i = n - 1; i >= 1; --i) {
            cnt[Max] ^= trie.query(a[i], Max);
            trie.insert(a[i], Max);
        }
    }
    int res = 0;
    for (int i = 0; i <= 25; ++i) {
        if (cnt[i] & 1)
            res |= 1 << i;
    }
    res >>= 1;
    printf("%d\n", res);
}

int main() {
    run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}

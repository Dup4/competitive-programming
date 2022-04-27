#pragma comment(linker, "/STACK:102400000,102400000")

//#include <cstdio>
//#include <cstring>
//#include <cctype>
//#include <cstdlib>
//#include <cmath>
//#include <climits>
//#include <ctime>
//#include <iostream>
//#include <algorithm>
//#include <deque>
//#include <vector>
//#include <queue>
//#include <string>
//#include <map>
//#include <stack>
//#include <set>
//#include <list>
//#include <bitset>
//#include <assert.h>
//#include <numeric>
//#include <sstream>
//#include <iomanip>
//#include <limits>

#include <bits/stdc++.h>

using namespace std;

namespace Dup4 {
typedef long long ll;
typedef long double ld;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, double> pid;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;

#define fi first
#define se second
#define pb push_back
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define p10 pc('\n')
#define L(on) ((on) << 1)
#define R(on) (L(on) | 1)
#define lowbit(x) ((x) & (-x))
#define mkp(a, b) make_pair(a, b)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define CLR(a, b) memset(a, (b), sizeof(a));
#define random(a, b) ((a) + rand() % ((b) - (a) + 1))
#define close()                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);
#define F(i, a, b) for (register int i = (a); i <= (b); ++i)
#define FF(i, a, b) for (register int i = (a); i >= (b); --i)

inline int read() {
    int x = 0, f = 1;
    char c = gc();
    for (; !isdigit(c); c = gc()) f ^= (c == '-');
    for (; isdigit(c); c = gc()) x = x * 10 + (c - '0');
    return x * (f ? 1 : -1);
}

template <typename T>
inline void read(T &x) {
    x = 0;
    int f = 1;
    char c = gc();
    for (; !isdigit(c); c = gc()) f ^= (c == '-');
    for (; isdigit(c); c = gc()) x = x * 10 + (c - '0');
    x *= f ? 1 : -1;
}

template <typename T>
inline void write(T x) {
    if (!x) {
        pc(48);
        return;
    }
    if (x < 0)
        x = -x, pc('-');
    int bit[20], i, p = 0;
    for (; x; x /= 10) bit[++p] = x % 10;
    for (i = p; i; --i) pc(bit[i] + 48);
}

//仅限于正整数读入

inline char nc() {
    static char buf[100000], *i = buf, *j = buf;
    return i == j && (j = (i = buf) + fread(buf, 1, 100000, stdin), i == j) ? EOF : *i++;
}

template <typename T>
inline void _read(T &sum) {
    char ch = nc();
    sum = 0;
    while (!(ch >= '0' && ch <= '9')) ch = nc();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
}

template <typename T>
inline T gcd(T a, T b) {
    while (b ^= a ^= b ^= a %= b)
        ;
    return a;
}

#ifdef LOCAL
#define gets gets_s
#define sp system("pause");
#define bug puts("***bug***");
#endif

#ifdef ONLINE_JUDGE
#define sp
#define bug
#endif

const double PI = acos(-1.0);
const double EI = exp(1.0);
const double eps = 1e-8;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fll;
}  // namespace Dup4

using namespace Dup4;

namespace FastIO {
// 只可读入 整数，单字符
#define BUF_SIZE 10000005
bool IOerror = false;
inline char NC() {
    static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
    if (p1 == pend) {
        p1 = buf;
        pend = buf + fread(buf, 1, BUF_SIZE, stdin);
        if (pend == p1) {
            IOerror = true;
            return -1;
        }
    }
    return *p1++;
}

inline bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

inline void __read(char &x) {
    char ch;
    while (blank(ch = NC()))
        ;
    if (IOerror) {
        x = -1;
        return;
    }
    x = ch;
}

template <typename T>
inline void __read(T &x) {
    char ch;
    while (blank(ch = NC()))
        ;
    if (IOerror) {
        x = -1;
        return;
    }
    bool flag = false;
    if (ch == '-') {
        flag = true;
        ch = NC();
    }
    for (x = ch - '0'; isdigit(ch = NC()); x = x * 10 + ch - '0')
        ;
    if (flag)
        x *= -1;
}
#undef BUF_SIZE
}  // namespace FastIO

using namespace FastIO;

const int maxn = (int)3e3 + 10;
const int Maxn = (int)1e6 + 10;
const int MOD = (int)9973;

int n, m;

int pre[maxn], tot[maxn], arr[maxn];

inline void Init() {
    F(i, 1, n) pre[i] = i;
    CLR(arr, 0);
    F(i, 1, n) tot[i] = 1;
}

inline int find(int x) {
    if (x != pre[x])
        pre[x] = find(pre[x]);
    return pre[x];
}

inline void join(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        pre[fx] = fy;
        tot[fy] += tot[fx];
    }
}

inline bool Input() {
    if (__read(n), __read(m), n == EOF)
        return false;
    int u, v, w;
    Init();
    F(i, 1, m) {
        __read(u), __read(v);
        __read(w);
        if (u == v)
            continue;
        join(u, v);
        arr[u] += w;
        arr[v] += w;
    }
    return true;
}

inline void Solve() {
    if (tot[find(1)] < n) {
        puts("0");
        return;
    }
    int Min = INF;
    F(i, 1, n) Min = min(Min, arr[i]);
    write(Min), p10;
}

inline void Run() {
#ifdef LOCAL
    freopen("Test.in", "r", stdin);
    // freopen("1.out", "w+", stdout);
#endif

    // t = read();
    while (Input()) Solve();

#ifdef LOCAL
    fclose(stdin);
    // fclose(stdout);
#endif
}

int main() {
    Run();
    return 0;
}

/*

*/

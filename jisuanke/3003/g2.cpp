#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 1e5 + 10;
const int M = 30;
int n, q, ans[N];
char s[N], t[N * 2];
ull base[M];
unordered_map<ull, int> mp;
struct node {
    int l, r, id;
};
vector<node> vec[N];
namespace IO {
const int S = (1 << 20) + 5;
// Input Correlation
char buf[S], *H, *T;
inline char Get() {
    if (H == T)
        T = (H = buf) + fread(buf, 1, S, stdin);
    if (H == T)
        return -1;
    return *H++;
}
inline int read() {
    int x = 0, fg = 1;
    char c = Get();
    while (!isdigit(c) && c != '-') c = Get();
    if (c == '-')
        fg = -1, c = Get();
    while (isdigit(c)) x = x * 10 + c - '0', c = Get();
    return x * fg;
}
inline void reads(char *s) {
    char c = Get();
    int tot = 0;
    while (c < 'a' || c > 'z') c = Get();
    while (c >= 'a' && c <= 'z') s[tot++] = c, c = Get();
    s[tot++] = '\0';
}
// Output Correlation
char obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[55];
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
inline void print(I x) {
    if (!x)
        putc('0');
    if (x < 0)
        putc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putc(qu[qr--]);
}
inline void prints(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) putc(s[i]);
    putc('\n');
}
inline void printd(int d, double x) {
    long long t = (long long)floor(x);
    print(t);
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
using namespace IO;
inline void getHash(int len) {
    ull Hs = 0;
    for (register int i = 1; i < len; ++i) {
        int c = s[i] - 'a' + 1;
        Hs += base[c];
    }
    for (register int i = len; i <= n; ++i) {
        int c = s[i] - 'a' + 1, pre = s[i - len + 1] - 'a' + 1;
        Hs += base[c];
        mp[Hs + base[0] * pre + base[27] * c]++;
        Hs -= base[pre];
    }
}
inline ull get(int l, int r) {
    ull Hs = 0;
    for (int i = l; i <= r; ++i) Hs += base[t[i] - 'a' + 1];
    Hs += base[0] * (t[l] - 'a' + 1) + base[27] * (t[r] - 'a' + 1);
    return Hs;
}

int main() {
    base[0] = 1;
    for (int i = 1; i < M; ++i) base[i] = base[i - 1] * 19260817;
    int _T;
    _T = read();
    while (_T--) {
        reads(s + 1);
        n = strlen(s + 1);
        q = read();
        int st = 0;
        for (int i = 1; i <= q; ++i) {
            reads(t + st);
            int len = strlen(t + st);
            vec[len].push_back({st, st + len - 1, i});
            st = st + len;
        }
        for (int i = 1; i <= n; ++i)
            if (!vec[i].empty()) {
                mp.clear();
                getHash(i);
                for (auto &it : vec[i]) {
                    ull Hs = get(it.l, it.r);
                    ans[it.id] = mp[Hs];
                }
            }
        for (int i = 1; i <= q; ++i) print(ans[i]), putc('\n');
    }
    flush();
    return 0;
}

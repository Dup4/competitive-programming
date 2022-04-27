#include <bits/stdc++.h>
using namespace std;
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
    while (c >= 'a' && c <= 'z') s[++tot] = c, c = Get();
    s[++tot] = '\0';
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
const int N = 1e6 + 10;
int n, q, op[N], x[N];

int main() {
    n = read();
    q = read();
    unordered_set<int> se;
    for (int i = 1; i <= q; ++i) {
        op[i] = read();
        x[i] = read();
        if (op[i] == 1) {
            se.insert(x[i] + 1);
        } else {
            se.insert(x[i]);
        }
    }
    for (int i = 1; i <= q; ++i) {
        if (op[i] == 1)
            se.erase(x[i]);
        else {
            auto pos = se.lower_bound(x[i]);
            if (pos == se.end())
                print(-1), putc('\n');
            else
                print(*pos), putc('\n');
        }
    }
    flush();
    return 0;
}

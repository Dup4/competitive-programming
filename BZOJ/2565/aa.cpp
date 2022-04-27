#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int maxn = 100010;
const int maxm = 1010;
const int maxs = 26;
const int INF = 1 << 29;
const int P = 1000000007;
const double error = 1e-9;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : 1), ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

struct pam {
    pam *fa, *next[maxs];
    int len;
} su[maxn], *headf, *heads, *last;

int n, pos, cnt, ans, f[maxn];
char s[maxn];

void init() {
    s[0] = '~', pos = 0;
    headf = &su[++cnt], last = heads = &su[++cnt];
    headf->fa = heads, heads->len = -1;
}

inline void add(int x) {
    pam *per = last;
    for (pos++; s[pos - per->len - 1] != s[pos]; per = per->fa)
        ;

    if (!per->next[x]) {
        pam *now = &su[++cnt];
        last = per->next[x] = now, now->len = per->len + 2;
        if (per == heads)
            now->fa = headf;
        else {
            for (per = per->fa; s[pos - per->len - 1] != s[pos]; per = per->fa)
                ;
            now->fa = per->next[x];
        }
    } else
        last = per->next[x];
}

int main() {
    scanf("%s", s + 1), n = strlen(s + 1), init();

    for (int i = 1; i <= n; i++) add(s[i] - 'a'), ans = max(ans, (f[i] = last->len) + f[i - f[i]]);

    printf("%d\n", ans);
    return 0;
}

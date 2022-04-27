#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e7 + 10;
typedef unsigned int ull;
struct Hash {
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * 131;
    }
    ull a[N];
    inline void gao(char *s) {
        a[0] = 0;
        for (int i = 1; s[i]; ++i) {
            a[i] = a[i - 1] * 131 + s[i];
        }
    }
    inline ull get(int l, int r) {
        return a[r] - a[l - 1] * base[r - l + 1];
    }
} hs;
ull Hash::base[N] = {0};
ll a, b;
int n;
char s[N];
void gett() {
    int i;
    for (i = 1; s[i]; ++i) {
        if (s[i] == '.')
            break;
    }
    n = 0;
    for (++i; s[i]; ++i) s[++n] = s[i];
}
int ord[N];

int main() {
    Hash::init();
    while (scanf("%lld%lld", &a, &b) != EOF) {
        scanf("%s", s + 1);
        gett();
        s[n + 1] = 0;
        hs.gao(s);
        ll res = a - b;
        for (int i = 0; i < 10; ++i) {
            int m = 0;
            for (int j = n; j >= 1; --j)
                if (s[j] == i + '0') {
                    ord[++m] = j;
                }
            if (!m)
                continue;
            ll l = n - ord[1] + 1;
            for (int j = 1; j <= m; ++j) {
                int it = ord[j];
                while (l < n) {
                    int nx = it + l + 1;
                    if (nx > n)
                        break;
                    if (s[it] == s[nx] && hs.get(nx, n) == hs.get(it, it + (n - nx)))
                        ++l;
                    else
                        break;
                }
                ll p = n - it + 1;
                res = max(res, a * p - b * l);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}

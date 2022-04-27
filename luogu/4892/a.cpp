#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 1e5 + 10;
int n, m;
char s[N], t[N];

struct Hash {
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * 131;
    }
    ull a[N];
    inline void gao(char *s) {
        a[0] = s[0];
        for (int i = 1; s[i]; ++i) {
            a[i] = a[i - 1] * 131 + s[i];
        }
    }
    inline ull get(int l, int r) {
        return a[r] - a[l - 1] * base[r - l + 1];
    }
} hs, ht;
ull Hash::base[N] = {0};

//二分求两个串的lcp
inline int gao(int x, int y) {
    int l = 1, r = min(n - x, m - y), res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (hs.get(x, x + mid - 1) == ht.get(y, y + mid - 1)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

//倍增求两个串的lcp
inline int gao2(int x, int y) {
    int res = 0;
    for (int i = 1 << 17; i >= 1; i >>= 1) {
        if (x + i - 1 < n && y + i - 1 < m && hs.get(x, x + i - 1) == ht.get(y, y + i - 1)) {
            x += i;
            y += i;
            res += i;
        }
    }
    return res;
}

//倍增高效求两个串的lcp
inline int gao3(int x, int y) {
    int k = 0, p = 1;
    while (p != 0) {
        if (hs.get(x, x + k + p - 1) == ht.get(y, y + k + p - 1)) {
            k += p;
            p <<= 1;
        } else {
            p >>= 1;
        }
        while (x + k + p > n || y + k + p > m) p >>= 1;
    }
    return k;
}

inline int ok(int x) {
    int y = 0;
    for (int j = 1; j <= 4; ++j) {
        int lcp = gao3(x, y);
        x += lcp + 1, y += lcp + 1;
        if (j == 4)
            return y > m;
        if (y >= m)
            return 1;
    }
    return 0;
}

void gogogo() {
    scanf("%s%s", s, t);
    hs.gao(s);
    ht.gao(t);
    n = strlen(s), m = strlen(t);
    if (n < m)
        return (void)puts("0");
    int res = 0;
    for (int i = 0; i + m - 1 < n; ++i) {
        res += ok(i);
    }
    printf("%d\n", res);
}

int main() {
    Hash::init();
    int T;
    scanf("%d", &T);
    while (T--) gogogo();
    return 0;
}

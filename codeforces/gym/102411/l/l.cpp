#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
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
    cout << arg << " ";
    err(args...);
}
const int N = 2e5 + 10;
int n, a, b;
char s[N];
vector<vector<int>> fac;
struct Hash {
    constexpr static ull seed = 233;
    static ull base[N];
    static void init() {
        base[0] = 1;
        for (int i = 1; i < N; ++i) base[i] = base[i - 1] * seed;
    }
    ull a[N];
    void gao(char *s) {
        a[0] = 0;
        for (int i = 1; s[i]; ++i) {
            a[i] = a[i - 1] * seed + s[i];
        }
    }
    ull get(int l, int r) {
        return a[r] - a[l - 1] * base[r - l + 1];
    }
} hs;
ull Hash::base[N] = {0};

int querylcp(int a, int b, int c, int d) {
    int l = 1, r = min(b - a + 1, d - c + 1), res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (hs.get(a, a + mid - 1) == hs.get(c, c + mid - 1)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

bool check(int x) {
    for (int i = 1; i + x - 1 <= n; ++i) {
        for (auto &y : fac[x]) {
            dbg(y, x);
            int len = x - y;
            if (hs.get(i, i + len - 1) == hs.get(i + y, i + x - 1)) {
                dbg(i, i + len - 1, i + y, i + x - 1);
                return true;
            }
        }
    }
    return false;
}

void gao(int y) {
    for (int i = 1; i + y - 1 <= n; ++i) {
        int lcp = querylcp(i, n, i + y, n);
        if (lcp) {
            int na = y + lcp, nb = y;
            int g = __gcd(na, nb);
            na /= g;
            nb /= g;
            if (1ll * na * b > 1ll * nb * a) {
                a = na;
                b = nb;
            }
        }
    }
}

int main() {
    Hash::init();
    fac.clear();
    fac.resize(N + 1);
    for (int i = 1; i <= 200000; ++i) {
        for (int j = i; j <= 200000; j += i) {
            fac[j].push_back(i);
        }
    }
    while (scanf("%s", s + 1) != EOF) {
        hs.gao(s);
        n = strlen(s + 1);
        int l = 1, r = n, res = 1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        a = res, b = 1;
        for (auto &y : fac[res]) {
            gao(y);
        }
        printf("%d/%d\n", a, b);
    }
    return 0;
}

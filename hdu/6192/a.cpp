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
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n;
char s[N];

typedef unsigned long long ull;
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
    ull get(int l, int r, int x, int y) {
        ull res = a[r] - a[l - 1] * base[r - l + 1];
        if (x >= l && x <= r) {
            res -= s[x] * base[r - x];
            res += s[y] * base[r - x];
        }
        return res;
    }
} hs;
ull Hash::base[N] = {0};

struct ExKMP {
    int Next[N];
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                Next[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }
} exkmp;

int main() {
    Hash::init();
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        exkmp.get_Next(s);
        hs.gao(s);
        if (n == 1) {
            puts("1 1");
            continue;
        }
        int res = INF, num = INF;
        for (int i = 2; i <= n; ++i) {
            int now = exkmp.Next[i];
            if (now == n - i + 1) {
                res = i - 1;
                num = n;
                break;
            } else {
                int x = 1 + now, y = i + now, len = n - i + 1;
                num = 0;
                num += hs.get(1, len, x, y) == hs.get(i, n, x, y);
                num += hs.get(1, len, y, x) == hs.get(i, n, y, x);
                if (num) {
                    res = i - 1;
                    break;
                }
            }
        }
        printf("%d %d\n", res, num);
    }
    return 0;
}

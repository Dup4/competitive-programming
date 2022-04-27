#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
char s[N];
ll mod = 1e9 + 7;
inline void add(ll &x, ll y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
struct node {
    ll a[4][4];
    node() {
        memset(a, 0, sizeof a);
    }
    inline void set() {
        memset(a, 0, sizeof a);
        for (int i = 0; i < 4; ++i) a[i][i] = 1;
    }
    inline node operator*(const node &other) const {
        node res = node();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < 4; ++k) add(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % mod);
        return res;
    }
    inline node operator^(ll n) {
        node res = node(), base = *this;
        res.set();
        while (n) {
            if (n & 1)
                res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
} base, res;

ll b[][4] = {2, 1, 1, 0, 1, 2, 0, 1, 1, 0, 2, 1, 0, 1, 1, 2};

int main() {
    while (scanf("%s", s + 1) != EOF) {
        if (s[1] == '0')
            break;
        int len = strlen(s + 1);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) base.a[i][j] = b[i][j];
        res = node();
        res.a[0][0] = 1;
        for (int i = len; i >= 1; --i) {
            int num = s[i] - '0';
            node tmp = base;
            while (num) {
                if (num & 1)
                    res = res * tmp;
                tmp = tmp * tmp;
                num >>= 1;
            }
            base = base ^ 10;
        }
        printf("%lld\n", res.a[0][0]);
    }
    return 0;
}

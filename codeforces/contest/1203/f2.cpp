#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
inline int rd() {
    int x;
    cin >> x;
    return x;
}
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
#define pii pair<int, int>
#define fi first
#define se second
int n, r, a[N], b[N];
void out(string s) {
    cout << s << "\n";
}
int gao1(int num, int r, vector<pii> vec) {
    int res = 0;
    sort(vec.begin(), vec.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se > y.se;
    });
    for (auto it : vec) {
        if (r >= it.fi && r + it.se >= 0) {
            r += it.se;
            ++res;
        }
    }
    return num + res;
}

int gao2(int num, int r, vector<pii> vec) {
    int res = 0;
    sort(vec.begin(), vec.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi > y.fi;
        return x.se > y.se;
    });
    for (auto it : vec) {
        if (r >= it.fi && r + it.se >= 0) {
            r += it.se;
            ++res;
        }
    }
    return num + res;
}

int gao3(int num, int r, vector<pii> vec) {
    int res = 0;
    sort(vec.begin(), vec.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se < y.se;
    });
    for (auto it : vec) {
        if (r >= it.fi && r + it.se >= 0) {
            r += it.se;
            ++res;
        }
    }
    return num + res;
}

int gao4(int num, int r, vector<pii> vec) {
    int res = 0;
    sort(vec.begin(), vec.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi > y.fi;
        return x.se < y.se;
    });
    for (auto it : vec) {
        if (r >= it.fi && r + it.se >= 0) {
            r += it.se;
            ++res;
        }
    }
    return num + res;
}
ll xtime() {
    return clock() * 1000 / CLOCKS_PER_SEC;
}
int gao5(int num, int r, vector<pii> vec) {
    int res = 0;
    mt19937 rnd(time(NULL));
    while (xtime() <= 1050) {
        shuffle(vec.begin(), vec.end(), rnd);
        int R = r, tmp = 0;
        for (auto it : vec) {
            if (R >= it.fi && R + it.se >= 0) {
                R += it.se;
                ++tmp;
            }
        }
        res = max(res, tmp);
    }
    return num + res;
}

void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    vector<pii> up, down;
    for (int i = 1; i <= n; ++i) {
        if (b[i] >= 0)
            up.push_back(pii(a[i], b[i]));
        else
            down.push_back(pii(a[i], b[i]));
    }
    sort(up.begin(), up.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se > y.se;
    });
    int num = 0;
    for (auto it : up) {
        if (r >= it.fi) {
            r += it.se;
            ++num;
        }
    }
    for (auto &it : down) it.se = -it.se, it.fi -= it.se;
    sort(down.begin(), down.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se > y.se;
    });
    int res = num;
    for (int i = 0; i <= r; ++i) {
        int tmp = 0, R = i;
        for (auto it : down) {
            if (R >= it.fi) {
                R += it.se;
                ++tmp;
            }
            if (R == r) {
                res = max(res, tmp + num);
            }
        }
    }
    for (auto &it : down) it.fi += it.se, it.se = -it.se;
    res = max(res, gao1(num, r, down));
    res = max(res, gao2(num, r, down));
    res = max(res, gao3(num, r, down));
    res = max(res, gao4(num, r, down));
    res = max(res, gao5(num, r, down));
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> r) run();
    return 0;
}

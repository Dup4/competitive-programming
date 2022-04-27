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
template <class T>
inline void out(T s) {
    cout << s << "\n";
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
int n, G[110][110];
inline void f5() {
    cout.flush();
}
inline int query(int x1, int y1, int x2, int y2) {
    cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    f5();
    return rd();
}
int Move[][2] = {0, -2, -2, 0, -1, -1};
inline bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n || G[x][y] == -1)
        return 0;
    return 1;
}
struct node {
    int x[2], y[2], ok;
    node() {}
    node(int x1, int y1, int x2, int y2, int _ok) {
        x[0] = x1;
        x[1] = x2;
        y[0] = y1;
        y[1] = y2;
        ok = _ok;
        //	cout << x[0] << " " << y[0] << " " << x[1] << " " << y[1] << " " << ok << endl;
    }
};
bool ispar(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}
vector<node> chvec;
bool check() {
    for (auto it : chvec) {
        string s = "", t = "";
        for (int i = it.x[0]; i <= it.x[1]; ++i) {
            s += G[i][it.y[0]] + '0';
        }
        for (int i = it.y[0] + 1; i <= it.y[1]; ++i) {
            s += G[it.x[1]][i] + '0';
        }
        for (int i = it.y[0]; i <= it.y[1]; ++i) {
            t += G[it.x[0]][i] + '0';
        }
        for (int i = it.x[0] + 1; i <= it.x[1]; ++i) {
            t += G[i][it.y[1]] + '0';
        }
        //	cout << s << " " << t << endl;
        if (it.ok) {
            if (!ispar(s) && !ispar(t))
                return 0;
        } else {
            if (ispar(s) || ispar(t))
                return 0;
        }
    }
    return 1;
}
void get() {
    chvec.clear();
    chvec.push_back(node(1, 2, 3, 3, query(1, 2, 3, 3)));
    chvec.push_back(node(1, 2, 2, 3, query(1, 2, 2, 3)));
    chvec.push_back(node(1, 2, 3, 2, query(1, 2, 3, 2)));
    chvec.push_back(node(2, 1, 3, 3, query(2, 1, 3, 3)));
    chvec.push_back(node(2, 1, 2, 3, query(2, 1, 2, 3)));
    chvec.push_back(node(2, 1, 3, 2, query(2, 1, 3, 2)));
    for (int i = 0; i < 2; ++i) {
        G[1][2] = i;
        for (int j = 0; j < 2; ++j) {
            G[2][1] = j;
            for (int k = 0; k < 2; ++k) {
                G[2][3] = k;
                for (int l = 0; l < 2; ++l) {
                    G[3][2] = l;
                    if (check()) {
                        return;
                    }
                }
            }
        }
    }
    assert(0);
}
void run() {
    memset(G, -1, sizeof G);
    G[1][1] = 1;
    G[n][n] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (G[i][j] != -1)
                continue;
            for (int k = 0; k < 3; ++k) {
                int x = i + Move[k][0];
                int y = j + Move[k][1];
                if (ok(x, y)) {
                    G[i][j] = query(x, y, i, j);
                    if (G[i][j])
                        G[i][j] = G[x][y];
                    else
                        G[i][j] = G[x][y] ^ 1;
                    break;
                }
            }
        }
    }
    get();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (G[i][j] != -1)
                continue;
            for (int k = 0; k < 3; ++k) {
                int x = i + Move[k][0];
                int y = j + Move[k][1];
                if (ok(x, y)) {
                    G[i][j] = query(x, y, i, j);
                    if (G[i][j])
                        G[i][j] = G[x][y];
                    else
                        G[i][j] = G[x][y] ^ 1;
                    break;
                }
            }
        }
    }
    out("!");
    f5();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << G[i][j];
            f5();
        }
        cout << "\n";
        f5();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}

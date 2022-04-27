#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
ll n;
int cnt[110], f[110];
const int mod = 1e9 + 7;
inline void chadd(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
template <int N, int M>
struct Matrix {
    int a[N][M];
    Matrix() {}
    int *operator[](int x) {
        return a[x];
    }
    void init() {
        memset(a, 0, sizeof a);
    }
    void set() {
        memset(a, 0, sizeof a);
        for (int i = 0; i < min(N, M); ++i) a[i][i] = 1;
    }
    void print() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d%c", a[i][j], " \n"[j == M - 1]);
            }
        }
    }
    template <int _N, int _M>
    Matrix operator*(const Matrix<_N, _M> &other) const {
        Matrix res = Matrix<N, _M>();
        res.init();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < _M; ++j) {
                for (int k = 0; k < M; ++k) {
                    chadd(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % mod);
                }
            }
        }
        return res;
    }
    Matrix qpow(long long n, Matrix base, Matrix res = Matrix<N, M>().set()) {
        while (n) {
            if (n & 1)
                res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
};

int main() {
    while (scanf("%lld", &n) != EOF) {
        vector<int> vec;
        for (int i = 1, sze; i <= 2; ++i) {
            scanf("%d", &sze);
            vector<int> tmp;
            for (int j = 1, x; j <= sze; ++j) {
                scanf("%d", &x);
                tmp.push_back(x);
            }
            sort(tmp.begin(), tmp.end());
            tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
            for (auto &it : tmp) ++cnt[it];
        }
        for (int i = 1; i <= 100; ++i) {
            if (cnt[i] == 2)
                vec.push_back(i);
        }
        f[0] = 1;
        for (int i = 1; i <= 100; ++i) {
            f[i] = 0;
            for (auto &it : vec) {
                if (i - it >= 0)
                    chadd(f[i], f[i - it]);
            }
        }
        if (n <= 100) {
            printf("%d\n", f[n]);
            continue;
        }
        Matrix<100, 100> base, res;
        base.init();
        res.init();
        for (int i = 0, j = 99; i < 100; ++i, --j) res[0][i] = f[j];
        for (int j = 0; j < 100; ++j) {
            if (j)
                base[j - 1][j] = 1;
            else {
                for (int i = 1; i <= 100; ++i) {
                    if (cnt[i] == 2) {
                        base[i - 1][j] = 1;
                    }
                }
            }
        }
        res = base.qpow(n - 99, base, res);
        printf("%d\n", res[0][0]);
    }
    return 0;
}

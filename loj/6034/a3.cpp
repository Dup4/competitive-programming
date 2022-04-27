#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
typedef double db;
const db INF = 2e18;
const db eps = 1e-10;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 1e5 + 10;

int main() {
    int m, q;
    while (scanf("%d%d", &m, &q) != EOF) {
        vector<pair<int, int>> X, Y;
        int op, x[2], y[2];
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < 2; ++j) {
                scanf("%d%d", x + j, y + j);
            }
            if (x[0] > x[1]) {
                swap(x[0], x[1]);
                swap(y[0], y[1]);
            }
            X.push_back(make_pair(x[0], x[1]));
            Y.push_back(make_pair(y[0], y[1]));
        }
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%d", &op);
            if (op == 0) {
                for (int j = 0; j < 2; ++j) {
                    scanf("%d%d", x + j, y + j);
                }
                if (x[0] > x[1]) {
                    swap(x[0], x[1]);
                    swap(y[0], y[1]);
                }
                X.push_back(make_pair(x[0], x[1]));
                Y.push_back(make_pair(y[0], y[1]));
            } else {
                int pos = 0;
                db Max = -INF;
                scanf("%d", x);
                for (int j = 0, sze = X.size(); j < sze; ++j) {
                    if (x[0] >= X[j].fi && x[0] <= X[j].se) {
                        db K = (Y[j].fi - Y[j].se) * 1.0 / (X[j].fi - X[j].se);
                        db B = Y[j].fi - K * X[j].fi;
                        if (K * x[0] + B > Max) {
                            Max = K * x[0] + B;
                            pos = j;
                        }
                    }
                }
                printf("%.6f %d %d %d %d\n", Max, X[pos].fi, Y[pos].fi, X[pos].se, Y[pos].se);
            }
        }
    }
    return 0;
}

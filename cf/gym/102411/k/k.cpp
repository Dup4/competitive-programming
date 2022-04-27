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
void err(const T& arg, const Ts&... args) {
    cout << arg << " ";
    err(args...);
}

const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m, ax, ay;
char str[N][N];
int up[N][N], down[N][N];
int X[N], Y[N];

void gaoA(int l, int r) {
    int MinU = INF, MinD = INF;
    for (int i = l; i <= r; ++i) {
        MinU = min(MinU, up[ax][i]);
        MinD = min(MinD, down[ax][i]);
    }
    for (int i = l; i <= r; ++i) {
        for (int j = 1; j <= MinU; ++j) {
            str[ax - j + 1][i] = 'a';
        }
        for (int j = 1; j <= MinD; ++j) {
            str[ax + j - 1][i] = 'a';
        }
    }
    str[ax][ay] = 'A';
}

void gaoU() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str[i][j] > 'A' && str[i][j] <= 'Z') {
                for (int o = 1;; ++o) {
                    if (i - o < 1)
                        break;
                    if (str[i - o][j] != '.')
                        break;
                    str[i - o][j] = str[i][j] - 'A' + 'a';
                }
            }
        }
    }
}

void gaoL() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str[i][j] > 'A' && str[i][j] <= 'Z') {
                int U = 0;
                for (int o = 1;; ++o) {
                    if (i - o < 1)
                        break;
                    if (str[i - o][j] != str[i][j] - 'A' + 'a')
                        break;
                    U = o;
                }
                for (int l = 1;; ++l) {
                    if (j - l < 1)
                        break;
                    int F = 1;
                    for (int o = 0; o <= U; ++o) {
                        if (str[i - o][j - l] != '.') {
                            F = 0;
                            break;
                        }
                    }
                    if (!F)
                        break;
                    for (int o = 0; o <= U; ++o) {
                        str[i - o][j - l] = str[i][j] - 'A' + 'a';
                    }
                }
            }
        }
    }
}

void gaoR() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str[i][j] > 'A' && str[i][j] <= 'Z') {
                int U = 0;
                for (int o = 1;; ++o) {
                    if (i - o < 1)
                        break;
                    if (str[i - o][j] != str[i][j] - 'A' + 'a')
                        break;
                    U = o;
                }
                for (int l = 1;; ++l) {
                    if (j + l > m)
                        break;
                    int F = 1;
                    for (int o = 0; o <= U; ++o) {
                        if (str[i - o][j + l] != '.') {
                            F = 0;
                            break;
                        }
                    }
                    if (!F)
                        break;
                    for (int o = 0; o <= U; ++o) {
                        str[i - o][j + l] = str[i][j] - 'A' + 'a';
                    }
                }
            }
        }
    }
}

void gaoD() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str[i][j] == '.') {
                str[i][j] = str[i - 1][j];
                if (str[i][j] > 'A' && str[i][j] <= 'Z')
                    str[i][j] = str[i][j] - 'A' + 'a';
            }
        }
    }
}

void print() {
    for (int i = 1; i <= n; ++i) printf("%s\n", str[i] + 1);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", str[i] + 1);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str[i][j] == 'A') {
                    ax = i, ay = j;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (i == 1) {
                    if (str[i][j] == '.' || str[i][j] == 'A')
                        up[i][j] = 1;
                    else
                        up[i][j] = 0;
                } else {
                    if (str[i][j] == '.' || str[i][j] == 'A')
                        up[i][j] = up[i - 1][j] + 1;
                    else
                        up[i][j] = 0;
                }
            }
        }
        for (int i = n; i >= 1; --i) {
            for (int j = 1; j <= m; ++j) {
                if (i == n) {
                    if (str[i][j] == '.' || str[i][j] == 'A')
                        down[i][j] = 1;
                    else
                        down[i][j] = 0;
                } else {
                    if (str[i][j] == '.' || str[i][j] == 'A')
                        down[i][j] = down[i + 1][j] + 1;
                    else
                        down[i][j] = 0;
                }
            }
        }
        // get A size
        int Max = -1, Maxl = -1, Maxr = -1;
        for (int l = 1; l <= m; ++l) {
            int MinU = INF, MinD = INF;
            for (int r = l; r <= m; ++r) {
                MinU = min(MinU, up[ax][r]);
                MinD = min(MinD, down[ax][r]);
                if (r >= ay && l <= ay) {
                    if (Max < (r - l + 1) * (MinU + MinD - 1)) {
                        Maxl = l, Maxr = r, Max = (r - l + 1) * (MinU + MinD - 1);
                    }
                }
            }
        }
        // color A size
        gaoA(Maxl, Maxr);
        gaoU();
        gaoL();
        gaoR();
        gaoD();
        print();
    }
    return 0;
}

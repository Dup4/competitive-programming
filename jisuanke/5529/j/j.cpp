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

int n;
int e[N][N];
int Max[N];
int now;
vector<vector<int> > vec;

void fix(int x, int y) {
    e[x][y] = e[y][x] = 1;
}

int find(int x) {
    while (e[Max[x]][x]) {
        ++Max[x];
    }
    return Max[x];
}

void insert(int x) {
    vec[now].push_back(x);
    if ((int)vec[now].size() == now + 1) {
        now--;
        if (now % 2 == 0)
            vec[now].push_back(x);
    }
}

void gao(int x, int y) {
    insert(x);
    int ny = y + 1;
    if (ny > n)
        return;
    insert(ny);
    gao(x + 1, ny);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                e[i][j] = (i == j ? 1 : 0);
            }
            Max[i] = 1;
        }
        vec.clear();
        vec.resize(n + 1);
        if (n & 1) {
            for (int cas = n - 1; cas >= 1; --cas) {
                vec[cas].push_back(n);
                int sze = 1;
                while (sze <= cas) {
                    int nxt = find(vec[cas].end()[-1]);
                    fix(vec[cas].end()[-1], nxt);
                    vec[cas].push_back(nxt);
                    sze++;
                }
            }
            for (int i = 1; i < n; ++i) {
                for (int j = 0, sze = vec[i].size(); j < sze; ++j) {
                    printf("%d%c", vec[i][j], " \n"[j == sze - 1]);
                }
            }
        } else {
            now = n - 1;
            //	insert(2);
            //	gao(1, 2);
            for (int i = 2; i <= n; i += 2) {
                insert(i);
                gao(1, i);
            }
            for (int i = 1; i < n; ++i) {
                for (int j = 0, sze = vec[i].size(); j < sze; ++j) {
                    printf("%d%c", vec[i][j], " \n"[j == sze - 1]);
                }
            }
        }
    }
    return 0;
}

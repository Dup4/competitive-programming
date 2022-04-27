#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
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

const int N = 2e5 + 10;
int n, a[N], b[N], need[N];
vector<vector<int>> G;

bool gao() {
    G.clear();
    G.resize(n + 1);
    vector<int> A, B;
    for (int i = 1; i <= n; ++i) {
        need[i] = a[i] - b[i];
        if (!b[i])
            A.push_back(i);
        else
            B.push_back(i);
    }
    if (SZ(B) == 1)
        return 0;
    for (int i = 0; i < SZ(B); ++i) {
        if (!i)
            G[B.back()].push_back(B[i]);
        else
            G[B[i - 1]].push_back(B[i]);
        --b[B[i]];
    }
    for (int i = 0; i < SZ(B); ++i) {
        for (int j = 0; b[B[i]] && j < SZ(B); ++j)
            if (i != j) {
                if (i == 0 && j == SZ(B) - 1)
                    continue;
                if (i != 0 && j == i - 1)
                    continue;
                --b[B[i]];
                G[B[j]].push_back(B[i]);
            }
        if (b[B[i]])
            return 0;
        for (int j = 0; need[B[i]] && j < SZ(A); ++j) {
            --need[B[i]];
            G[A[j]].push_back(B[i]);
        }
        if (need[B[i]])
            return 0;
    }
    sort(A.begin(), A.end(), [&](int x, int y) {
        return a[x] < a[y];
    });
    for (int i = 0; i < SZ(A); ++i) {
        if (a[A[i]] > i)
            return 0;
        for (int j = 0; a[A[i]] && j < i; ++j) {
            --a[A[i]];
            G[A[j]].push_back(A[i]);
        }
    }
    int sze = 0;
    for (int i = 1; i <= n; ++i) sze += SZ(G[i]);
    printf("%d\n", sze);
    for (int i = 1; i <= n; ++i) {
        for (auto& it : G[i]) {
            printf("%d %d\n", i, it);
        }
    }
    return 1;
}

int main() {
    // freopen("topo.in", "r", stdin);
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1; i <= n; ++i) scanf("%d", b + i);
        if (!gao())
            printf("-1\n");
    }
    return 0;
}

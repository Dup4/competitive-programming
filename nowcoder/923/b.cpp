#include <bits/stdc++.h>
using namespace std;

#define N 100010
vector<vector<int> > vec;
void init() {
    vec.clear();
    vec.resize(N);
    for (int i = 2; i < N; ++i) {
        if (vec[i].empty()) {
            for (int j = 2 * i; j < N; j += i) {
                vec[j].push_back(i);
            }
        }
    }
}
int n, m, aa[N], bb[N];
struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    void update(int l, int r, int v) {
        if (l > r) {
            return;
        }
        update(l, v);
        update(r + 1, -v);
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
} a, b;

bool ok() {
    for (int i = 100000; i >= 2; --i) {
        int A = a.query(i);
        int B = b.query(i);
        if (A + B) {
            int t = i;
            for (auto it : vec[i]) {
                while (t % it == 0) {
                    aa[it] += A;
                    bb[it] += B;
                    t /= it;
                }
            }
            if (t != 1) {
                aa[t] += A;
                bb[t] += B;
            }
            if (aa[i] != bb[i]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        a.init();
        b.init();
        memset(aa, 0, sizeof aa);
        memset(bb, 0, sizeof bb);
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            a.update(2, x, 1);
        }
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d", &x);
            b.update(2, x, 1);
        }
        puts(ok() ? "equal" : "unequal");
    }
    return 0;
}

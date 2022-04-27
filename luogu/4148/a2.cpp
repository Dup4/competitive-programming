#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
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
typedef int db;
const int N = 2e5 + 10;
const int DIM = 2;
const int K = 2;
int n;

struct Point {
    db x[DIM];
    db v;
    bool In(db Min[DIM], db Max[DIM]) {
        for (int i = 0; i < K; ++i) {
            if (x[i] < Min[i] || x[i] > Max[i])
                return 0;
        }
        return 1;
    }
};

struct KDTree {
    static constexpr double alpha = 0.725;
    struct cmpx {
        int div;
        cmpx(int div = 0) : div(div) {}
        bool operator()(const Point &a, const Point &b) {
            return a.x[div] < b.x[div];
            for (int i = 0; i < K; ++i)
                if (a.x[(i + div) % K] != b.x[(i + div) % K])
                    return a.x[(i + div) % K] < b.x[(i + div) % K];
            return true;
        }
    };
    bool cmp(const Point &a, const Point &b, int div) {
        return a.x[div] <= b.x[div];
    }
    struct Node {
        Point e;
        db Min[DIM], Max[DIM];
        int ls, rs;
        int div;
        int sze, sum;
        void init() {
            ls = rs = 0;
        }
        bool In(db _Min[DIM], db _Max[DIM]) {
            for (int i = 0; i < K; ++i) {
                if (_Min[i] > Min[i] || _Max[i] < Max[i])
                    return 0;
            }
            return 1;
        }
        bool Out(db _Min[DIM], db _Max[DIM]) {
            for (int i = 0; i < K; ++i) {
                if (_Max[i] < Min[i] || _Min[i] > Max[i])
                    return 1;
            }
            return 0;
        }
    } t[N];
    struct MStack {
        int tot;
        vector<int> vec;
        void init() {
            vec.clear();
            tot = 0;
        }
        int get() {
            int tar = 0;
            if (!vec.empty()) {
                tar = vec.back();
                vec.pop_back();
            } else {
                tar = ++tot;
            }
            return tar;
        }
        void save(int x) {
            vec.push_back(x);
        }
    } mStack;
    int root;
    void init() {
        root = 0;
        mStack.init();
    }
    int newnode() {
        int now = mStack.get();
        t[now].init();
        return now;
    }
    bool bad(int o) {
        return alpha * t[o].sze <= (double)max(t[t[o].ls].sze, t[t[o].rs].sze);
    }
    void pushup(int o) {
        t[o].sze = 1;
        t[o].sum = t[o].e.v;
        for (int i = 0; i < K; ++i) {
            t[o].Min[i] = t[o].Max[i] = t[o].e.x[i];
        }
        int ls = t[o].ls, rs = t[o].rs;
        if (ls) {
            t[o].sze += t[ls].sze;
            t[o].sum += t[ls].sum;
            for (int i = 0; i < K; ++i) {
                t[o].Min[i] = min(t[o].Min[i], t[ls].Min[i]);
                t[o].Max[i] = max(t[o].Max[i], t[ls].Max[i]);
            }
        }
        if (rs) {
            t[o].sze += t[rs].sze;
            t[o].sum += t[rs].sum;
            for (int i = 0; i < K; ++i) {
                t[o].Min[i] = min(t[o].Min[i], t[rs].Min[i]);
                t[o].Max[i] = max(t[o].Max[i], t[rs].Max[i]);
            }
        }
    }
    int build(int l, int r, vector<Point> &vec) {
        if (l > r)
            return 0;
        int mid = (l + r) >> 1;
        double avx[DIM] = {0}, vax[DIM] = {0};
        for (int i = l; i <= r; ++i)
            for (int j = 0; j < K; ++j) avx[j] += vec[i].x[j];
        for (int i = 0; i < K; ++i) avx[i] /= (double)(r - l + 1);
        for (int i = l; i <= r; ++i)
            for (int j = 0; j < K; ++j) vax[j] += (vec[i].x[j] - avx[j]) + (vec[i].x[j] - avx[j]);
        int o = newnode();
        t[o].div = 0;
        for (int i = 1; i < K; ++i) {
            if (vax[i] > vax[t[o].div])
                t[o].div = i;
        }
        nth_element(vec.begin() + l, vec.begin() + mid, vec.begin() + r + 1, cmpx(t[o].div));
        t[o].e = vec[mid];
        t[o].ls = build(l, mid - 1, vec);
        t[o].rs = build(mid + 1, r, vec);
        pushup(o);
        return o;
    }
    void dfs(int o, vector<Point> &vec) {
        if (!o)
            return;
        dfs(t[o].ls, vec);
        vec.push_back(t[o].e);
        mStack.save(o);
        dfs(t[o].rs, vec);
    }
    void rebuild(int &o) {
        vector<Point> vec;
        dfs(o, vec);
        o = build(0, SZ(vec) - 1, vec);
    }
    void insert(int &o, Point e) {
        if (!o) {
            o = newnode();
            t[o].e = e;
            pushup(o);
            return;
        }
        if (cmp(e, t[o].e, t[o].div)) {
            insert(t[o].ls, e);
        } else {
            insert(t[o].rs, e);
        }
        pushup(o);
        if (bad(o))
            rebuild(o);
    }
    int query(int o, db Min[DIM], db Max[DIM]) {
        if (!o || t[o].Out(Min, Max))
            return 0;
        if (t[o].In(Min, Max))
            return t[o].sum;
        int res = 0;
        if (t[o].e.In(Min, Max))
            res += t[o].e.v;
        return query(t[o].ls, Min, Max) + query(t[o].rs, Min, Max) + res;
    }
} kdTree;

int main() {
    int op, ans = 0;
    db Min[DIM], Max[DIM];
    Point e;
    kdTree.init();
    scanf("%d", &n);
    while (scanf("%d", &op) != EOF) {
        if (op == 1) {
            scanf("%d%d%d", e.x, e.x + 1, &e.v);
            e.x[0] ^= ans;
            e.x[1] ^= ans;
            e.v ^= ans;
            kdTree.insert(kdTree.root, e);
        } else if (op == 2) {
            for (int i = 0; i < K; ++i) {
                scanf("%d", Min + i);
                Min[i] ^= ans;
            }
            for (int i = 0; i < K; ++i) {
                scanf("%d", Max + i);
                Max[i] ^= ans;
            }
            printf("%d\n", ans = kdTree.query(kdTree.root, Min, Max));
            ans = 0;
        }
        if (op == 3)
            break;
    }
    return 0;
}

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
void err(const T& arg, const Ts&... args) {
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
} s[N];
int cntS;

struct KDTree {
    static constexpr double alpha = 0.725;
    struct cmpx {
        int div;
        cmpx(int div = 0) : div(div) {}
        bool operator()(const int& a, const int& b) {
            return s[a].x[div] < s[b].x[div];
        }
    };
    bool cmp(const int& a, const int& b, int div) {
        return s[a].x[div] <= s[b].x[div];
    }
    struct Node {
        int e;
        Node *ls, *rs;
        db Min[DIM], Max[DIM];
        int div;
        int sze, sum;
        void init() {
            e = 0;
            ls = rs = nullptr;
        }
        bool bad() {
            db lSze = 0, rSze = 0;
            if (ls)
                lSze = ls->sze;
            if (rs)
                rSze = rs->sze;
            return alpha * sze <= (double)max(lSze, rSze);
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
    } * root;
    struct MStack {
        Node pool[N], *tail;
        Node* bc[N];
        int top;
        void init() {
            top = 0;
            tail = pool;
        }
        Node* get() {
            if (!top)
                return tail++;
            return bc[top--];
        }
        void save(Node* t) {
            bc[++top] = t;
        }
    } mStack;
    void init() {
        mStack.init();
        root = nullptr;
    }
    Node* newnode() {
        Node* tmp = mStack.get();
        tmp->init();
        return tmp;
    }
    void pushup(Node* a) {
        a->sze = 1;
        a->sum = s[a->e].v;
        for (int i = 0; i < K; ++i) {
            a->Min[i] = a->Max[i] = s[a->e].x[i];
        }
        if (a->ls) {
            a->sze += a->ls->sze;
            a->sum += a->ls->sum;
            for (int i = 0; i < K; ++i) {
                a->Min[i] = min(a->Min[i], a->ls->Min[i]);
                a->Max[i] = max(a->Max[i], a->ls->Max[i]);
            }
        }
        if (a->rs) {
            a->sze += a->rs->sze;
            a->sum += a->rs->sum;
            for (int i = 0; i < K; ++i) {
                a->Min[i] = min(a->Min[i], a->rs->Min[i]);
                a->Max[i] = max(a->Max[i], a->rs->Max[i]);
            }
        }
    }
    Node* build(int l, int r, vector<int>& vec) {
        if (l > r)
            return nullptr;
        int mid = (l + r) >> 1;
        double avx[DIM] = {0}, vax[DIM] = {0};
        for (int i = l; i <= r; ++i)
            for (int j = 0; j < K; ++j) avx[j] += s[vec[i]].x[j];
        for (int i = 0; i < K; ++i) avx[i] /= (double)(r - l + 1);
        for (int i = l; i <= r; ++i)
            for (int j = 0; j < K; ++j) vax[j] += (s[vec[i]].x[j] - avx[j]) + (s[vec[i]].x[j] - avx[j]);
        Node* p = newnode();
        p->div = 0;
        for (int i = 1; i < K; ++i) {
            if (vax[i] > vax[p->div])
                p->div = i;
        }
        nth_element(vec.begin() + l, vec.begin() + mid, vec.begin() + r + 1, cmpx(p->div));
        p->e = vec[mid];
        p->ls = build(l, mid - 1, vec);
        p->rs = build(mid + 1, r, vec);
        pushup(p);
        return p;
    }
    void dfs(Node* t, vector<int>& vec) {
        if (!t)
            return;
        dfs(t->ls, vec);
        vec.push_back(t->e);
        mStack.save(t);
        dfs(t->rs, vec);
    }
    void rebuild(Node*& t) {
        vector<int> vec;
        dfs(t, vec);
        t = build(0, SZ(vec) - 1, vec);
    }
    void insert(Node*& t, int e) {
        if (!t) {
            t = newnode();
            t->e = e;
            pushup(t);
            return;
        }
        if (cmp(e, t->e, t->div)) {
            insert(t->ls, e);
        } else {
            insert(t->rs, e);
        }
        pushup(t);
        if (t->bad())
            rebuild(t);
    }
    int query(Node* t, db Min[DIM], db Max[DIM]) {
        if (!t || t->Out(Min, Max))
            return 0;
        if (t->In(Min, Max))
            return t->sum;
        int res = 0;
        if (s[t->e].In(Min, Max))
            res += s[t->e].v;
        return query(t->ls, Min, Max) + query(t->rs, Min, Max) + res;
    }
} kdTree;

int main() {
    int op, ans = 0;
    db Min[DIM], Max[DIM];
    cntS = 0;
    kdTree.init();
    scanf("%d", &n);
    while (scanf("%d", &op) != EOF) {
        if (op == 1) {
            ++cntS;
            scanf("%d%d%d", s[cntS].x, s[cntS].x + 1, &s[cntS].v);
            s[cntS].x[0] ^= ans;
            s[cntS].x[1] ^= ans;
            s[cntS].v ^= ans;
            kdTree.insert(kdTree.root, cntS);
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
        }
        if (op == 3)
            break;
    }
    return 0;
}

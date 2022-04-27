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
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
typedef long long db;
typedef long long ll;
const db INF = 1e18;
const db eps = 1e-10;
const db PI = acos(-1.0);
int sgn(db x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 4e5 + 10;

struct DCH {
    struct Point {
        db x, y;
        Point() {}
        Point(db _x, db _y) : x(_x), y(_y) {}
        Point operator-(const Point &t) const {
            return Point(x - t.x, y - t.y);
        }
        db operator^(const Point &t) const {
            return x * t.y - y * t.x;
        }
        db dis(Point b) {
            return hypot(x - b.x, y - b.y);
        }
    };
    struct node {
        Point p;
        mutable Point next_p;
        int opt;
        // 0 set中排序使用
        // 1 查询使用
        node(Point p = Point(0, 0), Point next_p = Point(0, 0), int opt = 0) : p(p), next_p(next_p), opt(opt) {}
        bool operator<(const node &other) const {
            if (opt) {
                return sgn(p.x * (other.next_p.x - other.p.x) + p.y * (other.next_p.y - other.p.y)) <= 0;
            } else {
                return sgn(p.x - other.p.x) == 0 ? sgn(p.y - other.p.y) < 0 : p.x < other.p.x;
            }
        }
    };
    set<node> st;
    //维护的是整个凸壳的面积和周长
    //整个凸包的面积就是两个凸壳的面积和
    //整个凸包的周长是两个凸壳的周长和
    db area, perimeter;
    typedef set<node>::iterator IT;
    void init() {
        st.clear();
        area = 0;
        perimeter = 0;
    }
    int size() {
        return st.size();
    }
    bool inside(const Point &p) const {
        if (st.empty())
            return 0;
        if (p.x < st.begin()->p.x)
            return 0;
        if (p.x > (--st.end())->p.x)
            return 0;
        IT lef = st.lower_bound(Point(p.x, -INF));
        if (p.x == lef->p.x)
            return p.y <= lef->p.y;
        IT rig = lef--;
        return sgn((p - lef->p) ^ (rig->p - lef->p)) >= 0;
    }
    void insert(Point p) {
        if (inside(p))
            return;
        st.insert(node(p, p));
        IT itr = st.lower_bound(p);
        if (itr != st.begin() && itr != (--st.end())) {
            IT lef = itr;
            lef--;
            IT rig = itr;
            rig++;
            lef->next_p = itr->p;
            itr->next_p = rig->p;
            area += (lef->p - p) ^ (rig->p - p);
            perimeter += p.dis(lef->p);
            perimeter += p.dis(rig->p);
            Point tmpp = lef->p;
            if ((int)st.size() > 3)
                perimeter -= tmpp.dis(rig->p);
        }
        if (itr == st.begin() && itr != (--st.end())) {
            IT rig = itr;
            rig++;
            itr->next_p = rig->p;
            area += (rig->p.x - p.x) * (p.y + rig->p.y);
            perimeter += p.dis(rig->p);
            if ((int)st.size() > 2) {
                Point tmpp = (--st.end())->p;
                perimeter -= tmpp.dis(rig->p);
                perimeter += tmpp.dis(p);
            }
        }
        if (itr != st.begin() && itr == (--st.end())) {
            IT lef = itr;
            lef--;
            lef->next_p = itr->p;
            area += (p.x - lef->p.x) * (p.y + lef->p.y);
            perimeter += p.dis(lef->p);
            if ((int)st.size() > 2) {
                Point tmpp = st.begin()->p;
                perimeter -= tmpp.dis(lef->p);
                perimeter += tmpp.dis(p);
            }
        }
        if (itr != st.begin()) {
            IT now = itr;
            now--;
            while (now != st.begin()) {
                IT tmp = now;
                tmp--;
                if (sgn((tmp->p - p) ^ (now->p - p)) >= 0) {
                    tmp->next_p = itr->p;
                    area += (tmp->p - p) ^ (now->p - p);
                    perimeter -= p.dis(now->p);
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(tmp->p);
                    perimeter += p.dis(tmp->p);
                    st.erase(now--);
                } else
                    break;
            }
            if (now->p.x == p.x) {
                if (now != st.begin()) {
                    IT tmp = now;
                    tmp--;
                    tmp->next_p = itr->p;
                }
                perimeter -= p.dis(now->p);
                if ((int)st.size() > 2) {
                    IT pre = now;
                    if (now == st.begin())
                        pre = (--st.end());
                    else
                        --pre;
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(pre->p);
                    perimeter += p.dis(pre->p);
                }
                st.erase(now);
            }
        }
        if (itr != (--st.end())) {
            IT now = itr;
            now++;
            while (now != (--st.end())) {
                IT tmp = now;
                tmp++;
                if (sgn((now->p - p) ^ (tmp->p - p)) >= 0) {
                    itr->next_p = tmp->p;
                    area += (now->p - p) ^ (tmp->p - p);
                    perimeter -= p.dis(now->p);
                    Point tmpp = now->p;
                    perimeter -= tmpp.dis(tmp->p);
                    perimeter += p.dis(tmp->p);
                    st.erase(now++);
                } else
                    break;
            }
        }
    }
    void insert(db x, db y = 0) {
        insert(Point(x, y));
    }
    //查询max(ax + by)
    db query(db a, db b) {
        if (size() == 0)
            return -INF;
        IT it = st.upper_bound(node(Point(a, b), Point(0, 0), 1));
        return it->p.x * a + b * it->p.y;
    }
};

struct SEG {
    DCH upHull[N << 2], downHull[N << 2];
    void build(int id, int l, int r) {
        upHull[id].init();
        downHull[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void ins(int id, int l, int r, int pos, db x, db y) {
        upHull[id].insert(x, y);
        downHull[id].insert(x, -y);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            ins(id << 1, l, mid, pos, x, y);
        else
            ins(id << 1 | 1, mid + 1, r, pos, x, y);
    }
    db query(int id, int l, int r, int ql, int qr, db x, db y) {
        if (l >= ql && r <= qr) {
            if (y > 0)
                return upHull[id].query(x, y);
            else
                return downHull[id].query(x, -y);
        }
        int mid = (l + r) >> 1;
        db Max = -INF;
        if (ql <= mid)
            Max = max(Max, query(id << 1, l, mid, ql, qr, x, y));
        if (qr > mid)
            Max = max(Max, query(id << 1 | 1, mid + 1, r, ql, qr, x, y));
        return Max;
    }
} seg;

int main() {
    ll lst = 0;
    int n = 0;
    int q;
    char dataTp[10];
    scanf("%d%s", &q, dataTp);
    seg.build(1, 1, q);
    for (int i = 1; i <= q; ++i) {
        char op[5];
        int l, r;
        ll x, y;
        scanf("%s", op);
        scanf("%lld%lld", &x, &y);
        x ^= lst;
        y ^= lst;
        if (op[0] == 'A') {
            ++n;
            seg.ins(1, 1, q, n, x, y);
        } else {
            scanf("%d%d", &l, &r);
            l ^= lst;
            r ^= lst;
            lst = seg.query(1, 1, q, l, r, x, y);
            printf("%lld\n", lst);
            if (dataTp[0] == 'E')
                lst = 0;
            lst &= 0x7fffffff;
        }
    }
    return 0;
}

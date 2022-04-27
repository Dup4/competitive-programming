#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = LLONG_MAX >> 1;

long long gety(long long x, long long k, long long d) {
    return k * x + d;
}

struct SegT {
    struct Node {
        Node *lc, *rc;
        long long k, d, min;
        int l, r, minid, rl, rr;

        Node() {}
        Node(int pos) : lc(NULL), rc(NULL), l(pos), r(pos), k(0), d(INF), min(INF), minid(-1), rl(pos), rr(pos) {}
        Node(Node *lc, Node *rc) : lc(lc), rc(rc), l(lc->l), r(rc->r), k(0), d(INF) {
            maintain();
        }

        long long gety(long long x) {
            return x * k + d;
        }

        void maintain() {
            rl = (lc->rl != -1 ? lc->rl : rc->rl);
            rr = (rc->rr != -1 ? rc->rr : lc->rr);
            calc();
            if (lc->min < min) {
                min = lc->min;
                minid = lc->minid;
            }
            if (rc->min < min) {
                min = rc->min;
                minid = rc->minid;
            }
        }

        void calc() {
            min = INF;
            minid = -1;
            if (rl != -1 && gety(rl) < min) {
                min = gety(rl);
                minid = rl;
            }
            if (rr != -1 && gety(rr) < min) {
                min = gety(rr);
                minid = rr;
            }
        }

        void update(long long k, long long d) {
            if (gety(rl) > ::gety(rl, k, d) && gety(rr) > ::gety(rr, k, d)) {
                this->k = k;
                this->d = d;
                l == r ? calc() : maintain();
                return;
            }
            if (gety(rl) <= ::gety(rl, k, d) && gety(rr) <= ::gety(rr, k, d))
                return;

            int mid = l + ((r - l) >> 1);
            if (gety(rr) > ::gety(rr, k, d)) {
                std::swap(this->k, k);
                std::swap(this->d, d);
            }
            if (gety(mid) > ::gety(mid, k, d)) {
                std::swap(this->k, k);
                std::swap(this->d, d);
                rc->update(k, d);
            } else {
                lc->update(k, d);
            }
            maintain();
        }

        void update(int l, int r, long long k, long long d) {
            if (l > this->r || this->l > r)
                return;
            if (l <= this->l && this->r <= r) {
                update(k, d);
                return;
            }
            lc->update(l, r, k, d);
            rc->update(l, r, k, d);
            maintain();
        }

        void erase(int pos) {
            if (l == r) {
                rl = rr = -1;
                k = 0;
                d = INF;
                calc();
                return;
            }
            int mid = l + ((r - l) >> 1);
            (pos <= mid ? lc : rc)->erase(pos);
            maintain();
        }
    } * root, _pool[MAXN << 1], *_curr;

    Node *build(int l, int r) {
        if (l == r)
            return new (_curr++) Node(l);
        int mid = l + ((r - l) >> 1);
        return new (_curr++) Node(build(l, mid), build(mid + 1, r));
    }

    void init(int n) {
        _curr = _pool;
        root = build(1, n);
    }

    void update(int l, int r, long long k, long long d) {
        root->update(l, r, k, d);
    }

    void erase(int pos) {
        root->erase(pos);
    }
} segT;

struct Edge {
    int l, r;
    long long k, d;
    Edge(int l, int r, long long k, long long d) : l(l), r(r), k(k), d(d) {}
};
std::vector<Edge> G[MAXN];

long long dist[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0, x, l, r; i < m; i++) {
        long long k, d;
        scanf("%d %d %d %lld %lld", &x, &l, &r, &d, &k);
        G[x].emplace_back(l, r, k, d - l * k);
    }

    segT.init(n);
    segT.update(1, 1, 0, 0);
    std::fill(dist + 1, dist + n + 1, -1);
    for (int _ = 0; _ < n; _++) {
        int u = segT.root->minid;
        if (u == -1)
            break;
        cout << u << "\n";
        dist[u] = segT.root->min;
        if (dist[u] >= INF)
            break;
        for (const Edge &e : G[u]) segT.update(e.l, e.r, e.k, e.d + dist[u]);
        segT.erase(u);
    }

    for (int i = 1; i <= n; i++) printf("%lld ", dist[i]);
    puts("");

    return 0;
}

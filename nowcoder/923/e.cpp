#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define seit multiset<int>::iterator
int n, m, q, a[N], b[N];
struct node {
    int v;
    seit it[2];
    node() {}
    node(int v, seit it1, seit it2) {
        this->v = v;
        it[0] = it1;
        it[1] = it2;
    }
    bool operator<(const node &other) const {
        return v > other.v;
    }
};

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", b + i);
        }
        multiset<int> se[2];
        char op[10];
        int v, x = 0, y = 0;
        se[0].insert(b[0]);
        se[1].insert(a[0]);
        priority_queue<node> pq;
        for (int i = 1; i <= q; ++i) {
            scanf("%s%d", op, &v);
            switch (op[0]) {
                case 'R':
                    while (v-- && y < m - 1) {
                        ++y;
                        se[0].insert(b[y]);
                    }
                    break;
                case 'D':
                    while (v-- && x < n - 1) {
                        ++x;
                        se[1].insert(a[x]);
                    }
                    break;
                case 'Q':
                    while (!pq.empty()) pq.pop();
                    pq.push(node(*se[0].begin() + *se[1].begin(), se[0].begin(), se[1].begin()));
                    for (int j = 1; j <= v; ++j) {
                        node t = pq.top();
                        pq.pop();
                        printf("%d%c", t.v, " \n"[j == v]);
                        seit it[2];
                        it[0] = t.it[0];
                        it[1] = t.it[1];
                        ++it[1];
                        if (it[1] != se[1].end()) {
                            pq.push(node(*it[0] + *it[1], it[0], it[1]));
                        }
                        --it[1];
                        ++it[0];
                        if (it[1] == se[1].begin() && it[0] != se[0].end()) {
                            pq.push(node(*it[0] + *it[1], it[0], it[1]));
                        }
                    }
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}

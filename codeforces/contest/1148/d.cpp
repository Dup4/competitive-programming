#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n;
struct node {
    int a, b, id;
    node() {}
    node(int a, int b, int id) : a(a), b(b), id(id) {}
    void scan(int id) {
        this->id = id;
        scanf("%d%d", &a, &b);
    }
};

int main() {
    while (scanf("%d", &n) != EOF) {
        vector<node> a, b;
        a.clear();
        b.clear();
        for (int i = 1, x, y; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            if (x < y) {
                a.push_back(node(x, y, i));
            } else {
                b.push_back(node(x, y, i));
            }
        }
        if (a.size() > b.size()) {
            int sze = (int)a.size();
            printf("%d\n", sze);
            sort(a.begin(), a.end(), [&](node a, node b) {
                return a.a > b.a;
            });
            for (int i = 0; i < sze; ++i) {
                printf("%d%c", a[i].id, " \n"[i == sze - 1]);
            }
        } else {
            int sze = (int)b.size();
            printf("%d\n", sze);
            sort(b.begin(), b.end(), [&](node a, node b) {
                return a.a < b.a;
            });
            for (int i = 0; i < sze; ++i) {
                printf("%d%c", b[i].id, " \n"[i == sze - 1]);
            }
        }
    }
    return 0;
}

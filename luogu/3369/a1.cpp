#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using pII = pair<int, int>;
#define fi first
#define se second
tree<pII, null_type, less<pII>, rb_tree_tag, tree_order_statistics_node_update> rbtree;

int main() {
    int n;
    scanf("%d", &n);
    rbtree.clear();
    int op, x;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &op, &x);
        if (op == 1) {
            rbtree.insert(pII(x, i));
        } else if (op == 2) {
            rbtree.erase(rbtree.lower_bound(pII(x, 0)));
        } else if (op == 3) {
            printf("%d\n", (int)rbtree.order_of_key(pII(x, 0)) + 1);
        } else if (op == 4) {
            int ans = rbtree.find_by_order(x - 1)->fi;
            printf("%d\n", ans);
        } else if (op == 5) {
            int ans = (--rbtree.lower_bound(pII(x, 0)))->fi;
            printf("%d\n", ans);
        } else if (op == 6) {
            int ans = rbtree.upper_bound(pII(x, n))->fi;
            printf("%d\n", ans);
        }
    }
    return 0;
}

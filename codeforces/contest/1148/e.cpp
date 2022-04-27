#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define pii pair<int, int>
#define se second
#define fi first
int n, t[N];
pii s[N];
pii sta[N << 1];
int top;
struct node {
    int i, j, d;
    node() {}
    node(int i, int j, int d) : i(i), j(j), d(d) {}
};

void work() {
    top = 0;
    vector<node> res;
    for (int i = 1; i <= n; ++i) {
        int gap = t[i] - s[i].fi;
        //向右移动
        if (gap > 0) {
            sta[++top] = pii(gap, s[i].se);
        } else if (gap < 0) {
            int need = -gap;
            while (top > 0) {
                pii tmp = sta[top];
                --top;
                if (tmp.fi > need) {
                    res.push_back(node(tmp.se, s[i].se, need));
                    tmp.fi -= need;
                    need = 0;
                    sta[++top] = tmp;
                    break;
                } else {
                    res.push_back(node(tmp.se, s[i].se, tmp.fi));
                    need -= tmp.fi;
                }
            }
            if (need > 0) {
                puts("NO");
                return;
            }
        }
    }
    if (top) {
        puts("NO");
        return;
    }
    puts("YES");
    int sze = (int)res.size();
    printf("%d\n", sze);
    for (auto it : res) {
        printf("%d %d %d\n", it.i, it.j, it.d);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &s[i].fi);
            s[i].se = i;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", t + i);
        }
        sort(s + 1, s + 1 + n);
        sort(t + 1, t + 1 + n);
        work();
    }
    return 0;
}

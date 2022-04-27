#include <bits/extc++.h>
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace __gnu_pbds;
using namespace std;
using pII = pair<int, int>;
using ll = long long;
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
constexpr int N = 1e6 + 10;
int n, m, a[N], f[N];
unordered_map<int, int> cnt;

template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct map_node_update {
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    typedef int metadata_type;
    const static int INF = 0x3f3f3f3f;
    void operator()(Node_Itr it, Node_CItr end_it) {
        Node_Itr l = it.get_l_child();
        Node_Itr r = it.get_r_child();
        metadata_type left = 0, right = 0;
        if (l != end_it)
            left = l.get_metadata();
        if (r != end_it)
            right = r.get_metadata();
        const_cast<metadata_type&>(it.get_metadata()) = left + right + (*it)->second;
    }
    metadata_type querysum(pII x) {
        metadata_type ans = 0;
        Node_CItr it = node_begin();
        while (it != node_end()) {
            Node_CItr l = it.get_l_child();
            Node_CItr r = it.get_r_child();
            // x比当前节点要小，走向左儿子
            if (Cmp_Fn()(x, (*it)->first)) {
                it = l;
            } else {
                // x大于等于当前节点
                ans += (*it)->second;
                if (l != node_end())
                    ans += l.get_metadata();
                it = r;
            }
        }
        return ans;
    }
    //[l, r]范围内的权值
    metadata_type querysum(int l, int r) {
        if (l > r)
            return 0;
        return querysum(pII(r, INF)) - querysum(pII(l, -INF));
    }
};
// pII fi key se id Mapeed value
//不可使用非标准的[]操作, 为了防止重复,用pair当键值, se是id
tree<pII, int, less<pII>, rb_tree_tag, map_node_update> rbtree;

int main() {
    scanf("%d", &n);
    cnt.clear();
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        ++cnt[a[i]];
        f[i] = cnt[a[i]];
    }
    cnt.clear();
    rbtree.clear();
    ll res = 0;
    for (int i = n; i >= 1; --i) {
        ++cnt[a[i]];
        res += rbtree.querysum(1, f[i] - 1);
        rbtree.insert(make_pair(pII(cnt[a[i]], i), 1));
    }
    printf("%lld\n", res);
    return 0;
}

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fi first
#define se second
using namespace __gnu_pbds;
using namespace std;
using pII = pair <int, int>;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
constexpr int N = 1e6 + 10;
int n, m, a[N], f[N];
unordered_map <int, int> cnt;

template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update {
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    typedef int metadata_type;
    void operator() (Node_Itr it, Node_CItr end_it) {
        Node_Itr l = it.get_l_child();
        Node_Itr r = it.get_r_child();
        int left = 0, right = 0;
        if(l != end_it) left = l.get_metadata();
        if(r != end_it) right = r.get_metadata();
        const_cast<metadata_type &>(it.get_metadata()) = 
			left + right + (*it)->second;
    }
	//找有多少个元素小于等于当前元素
    int order_of_key (int x) { 
        int ans = 0;
        Node_CItr it = node_begin();
        while(it != node_end()) {
            Node_CItr l = it.get_l_child();
            Node_CItr r = it.get_r_child();
			//x比当前点小, 直接往左儿子走
            if(Cmp_Fn()(x, (*it)->first)) {
                it = l;
    		} else {
                ans += (*it)->second; 
                if(l != node_end()) ans += l.get_metadata();
                it = r;
            }
        }
        return ans;
    }
	int querysum(int x) {
		int ans = 0;
        Node_CItr it = node_begin();
		while (it != node_end()) {
			Node_CItr l = it.get_l_child();
			Node_CItr r = it.get_r_child();
            if(Cmp_Fn()(x, (*it)->first)) {
                it = l;
    		} else {
				ans += (*it)->second;
                if(l != node_end()) ans += l.get_metadata();
                it = r;
            }
		}
		return ans;
	}
	int querysum(int l, int r) {
		if (l > r) return 0;
		return querysum(r) - querysum(l - 1);
	}
};
tree<int, int, less<int>, rb_tree_tag, my_node_update> rbtree; 
//tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> rbtree;

int main() {
//	rbtree.clear(); 
//	rbtree.insert(make_pair(5, 5));
//	rbtree.insert(make_pair(4, 5));
//	rbtree.insert(make_pair(5, 6));
//	rbtree[5] = 3;
//	rbtree[4] = 5;
//	for (auto &it : rbtree)
//		cout << it.first << " " << it.second << endl;
//	cout << rbtree.order_of_key(5) << endl;
//	cout << rbtree[-5] << endl;
//	return 0;
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
		res += rbtree.querysum(f[i] - 1);
		auto pos = rbtree.lower_bound(cnt[a[i]]);
		if (pos != rbtree.end() && pos->first == cnt[a[i]]) {
			int tmp = pos->second;
			rbtree.erase(cnt[a[i]]);
			rbtree[cnt[a[i]]] = tmp + 1;
	//		rbtree.insert(make_pair(cnt[a[i]], tmp + 1));
		} else {
			rbtree[cnt[a[i]]] = 1;
	//		rbtree.insert(make_pair(cnt[a[i]], 1));
		}
	//	cout << "-----------------\n";
	//	for (auto &it : rbtree)
	//		cout << it.first << " " << it.second << endl;
	}
	printf("%lld\n", res);
	return 0;
}

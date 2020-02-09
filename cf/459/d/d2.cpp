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

template<class Node_CItr,class Node_Itr,class Cmp_Fn,class _Alloc>
struct my_node_update {
    typedef int metadata_type;
    int order_of_key (pair<int,int> x) {
        int ans = 0;
        Node_CItr it = node_begin();
        while(it != node_end()) {
            Node_CItr l = it.get_l_child();
            Node_CItr r = it.get_r_child();
            if(Cmp_Fn()(x, **it)) {
                it = l;
    		} else {
                ans++;
                if(l != node_end()) ans += l.get_metadata();
                it = r;
            }
        }
        return ans;
    }
    void operator() (Node_Itr it, Node_CItr end_it) {
        Node_Itr l = it.get_l_child();
        Node_Itr r = it.get_r_child();
        int left = 0,right = 0;
        if(l != end_it) left = l.get_metadata();
        if(r != end_it) right = r.get_metadata();
        const_cast<int&>(it.get_metadata()) = left + right + (*it)->first;
		cout << ((**it).second) << endl;
    }
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
};
tree<pII, int, less<pII>, rb_tree_tag, my_node_update> rbtree; 

int main() {
	scanf("%d", &n);
	rbtree.clear();
	cnt.clear();
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		++cnt[a[i]];
		f[i] = cnt[a[i]];
	}
	cnt.clear();
	ll res = 0;
	for (int i = n; i >= 1; --i) {
		++cnt[a[i]];
		res += rbtree.order_of_key(pII(f[i], 0));
		rbtree.insert(pII(cnt[a[i]], i)); 	
	}
	printf("%lld\n", res);
	return 0;
}

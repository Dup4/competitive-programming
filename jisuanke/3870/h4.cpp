#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
const int mod = 998244353;
const int N = 1e7 + 10;
int q; ll n, ans, A[N], F[N], gn[N];
inline void add(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod; 
}
struct node {
    int a[2][2];
    node() {
        memset(a, 0, sizeof a);
    }
    inline void set() {
        memset(a, 0, sizeof a);
        a[0][0] = a[1][1] = 1;
    }
    inline node operator * (const node &other) const {
        node res = node();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    add(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % mod); 
        return res;
    }
    inline node operator ^ (int n) {
        node res = node(), base = *this; res.set();
        while (n) {
            if (n & 1) res = res * base;
            base = base * base; 
            n >>= 1;
        }
        return res;
    }
}base[21], base2[21][20], res; 

inline int get(ll n) {
	res = node(); res.a[0][0] = 1;
	for (int j = 0; ; ++j) {
		if (!n) break;
		int num = n % 10; n /= 10;
	    if (num) res = res * base2[j][num]; 
	}
	return res.a[0][1]; 
}
unordered_map <int, int> mp;

void gao() {
	mp.clear(); 
	gn[1] = n;
	ans = 0;
	for (int i = 1; i <= q; ++i) {
		if (mp.count(gn[i] % (mod - 1))) {
			A[i] = mp[gn[i] % (mod - 1)];
		} else {
			A[i] = get(gn[i] % (mod - 1));
		    mp[gn[i] % (mod - 1)] = A[i];	
		}
		gn[i + 1] = gn[i] ^ (A[i] * A[i]);
		ans ^= A[i];
	}
	printf("%lld\n", ans);
}

int main() {
	base[0] = node();
	base[0].a[0][0] = 3; base[0].a[0][1] = 1; 
	base[0].a[1][0] = 2; 
	for (int j = 1; j <= 9; ++j) {
		base2[0][j].set();
		node tmp = base[0];
		int t = j;
		while (t) {
			if (t & 1) base2[0][j] = base2[0][j] * tmp;
			tmp = tmp * tmp;
			t >>= 1;
		}
	}
	for (int i = 1; i <= 20; ++i) {
		base[i] = base[i - 1] ^ 10;   
		for (int j = 1; j <= 9; ++j) {
			base2[i][j].set();
			node tmp = base[i]; 
			int t = j;
			while (t) { 
				if (t & 1) base2[i][j] = base2[i][j] * tmp;
				tmp = tmp * tmp;
				t >>= 1;
			}
		}
	}
	while (scanf("%d%lld", &q, &n) != EOF) {
		gao();
	}
    return 0;
}



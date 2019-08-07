#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 250010
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}
struct frac{
    ll x,y;
	inline void sim() {
		ll g = gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		if (x * y < 0) {
			x = -abs(x);
			y = abs(y);
		} else {
			x = abs(x);
			y = abs(y);
		}
	}
	frac() {}
	frac(ll x, ll y) : x(x), y(y) {sim();}
    frac operator+(const frac &u){
        ll p, q; 
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator-(const frac &u){
        ll p, q;
        p = x * u.y - y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator*(const frac &u){
        ll p, q;
        p = u.x * x;
        q = u.y * y;
        ll d = gcd(p, q); 
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator/(const frac &u){
        ll p, q;
        p = u.y * x;
        q = u.x * y;
        ll d = gcd(p,q);
        p /= d; q /= d;
        return (frac){p,q};
    }
	bool operator < (const frac &other) const {
		return x * other.y < y * other.x;
	}
	bool operator != (const frac &other) const {
		return x * other.y != y * other.x;
	}
	bool operator <= (const frac &other) const {
		return x * other.y <= y * other.x;
	}
	bool operator >= (const frac &other) const {
		return x * other.y >= y * other.x;
	}
	bool operator == (const frac &other) const {
		return x * other.y == y * other.x;
	}
	void sqr() {
		*this = (*this) * (*this);
	}
    void print(){
		sim();
		if (x * y < 0) putchar('-');
		printf("%lld/%lld\n", abs(x), abs(y));
    }
};
struct node {
	ll a, b; 
	frac x;
	int id; 
	node() {}
	void scan(int _id) {
		scanf("%lld%lld", &a, &b);  
		id = _id;
		x = frac(a, a + b);
	}
	bool operator < (const node &other) const {
		return x < other.x;
	}
}a[N];
int n, p[N], fp[N]; 
frac res[N];

struct BIT {
	ll a[N << 1];
	void init(int n) {
		for (int i = 0; i <= n; ++i)
			a[i] = 0;
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}A, B;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); A.init(2 * n); B.init(2 * n);
		for (int i = 1; i <= n; ++i) a[i].scan(i);
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			p[a[i].id] = i;
		}
		for (int i = 1; i <= n; ++i) {
			A.update(p[i], a[p[i]].a);
			B.update(p[i], a[p[i]].b);
			if (i == 1) {
				res[i] = frac(a[p[1]].b, a[p[1]].a + a[p[1]].b);
			} else {
				int l = 1, r = n, pos = -1;
				while (r - l >= 0) {
					int mid = (l + r) >> 1;
			//		cout << "# " << mid << " " << A.query(1, mid) << " " << B.query(mid + 1, n) << endl; 
					if (A.query(1, mid - 1) <= B.query(mid + 1, n)) {
						pos = mid;
						l = mid + 1;
					} else {
						r = mid - 1;
					}
				}
				int Sa = A.query(1, pos - 1), Sb = B.query(pos + 1, n);
			//	cout << i << " " << Sa << " " << Sb << " " << pos << endl;
				int p = a[pos].a;
				if (a[pos].id > i) {
					p = 0;
				}
				if (Sa + p == Sb) {
					res[i] = frac(Sa + p, 1);
				} else {
					frac x = frac(Sb - Sa + a[pos].b, a[pos].a + a[pos].b);
					res[i] = x * frac(a[pos].a, 1) + frac(Sa, 1);
				}
			}
			res[i].print();
		}
	}
	return 0;
}

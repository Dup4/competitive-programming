#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
const db PI = acos(-1.0); 
const int N = 1e5 + 10;
const int M = N * 4;
int n, a[3][N], cnt[3], len, tot; ll num[M], sum[M];
struct Complex {
	db x, y;
	Complex(db _x = 0.0, db _y = 0.0) { x = _x, y = _y; }
	Complex operator - (const Complex &b) const { return Complex(x - b.x, y - b.y); }
	Complex operator + (const Complex &b) const { return Complex(x + b.x, y + b.y); }
	Complex operator * (const Complex &b) const { return Complex(x * b.x - y * b.y, x * b.y + y * b.x); }
}x1[M], x2[M]; 
struct FFT {
	//进行FFT和IFFT的反转变换
	//位置i和(i 二进制反转后位置)互转
	//len 必须为2的幂次
	void change(Complex *y, int len) {
		int i, j, k;
		for (i = 1, j = len / 2; i < len - 1; ++i) {
			if (i < j) swap(y[i], y[j]);
			//交换互为下标反转的元素 i < j 保证交换一次
			//i 做正常的 + 1 j 做反转类型的 + 1 始终保持i 和 j 是反转的
			k = len / 2;
			while (j >= k) {
				j -= k;
				k /= 2;
			}
			if (j < k) j += k;
		}
	}
	//on = 1 DFT
	//on = -1 IDFT
	void gao(Complex *y, int len, int on) {
		change(y, len);
		for (int h = 2; h <= len; h <<= 1) {
			Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
			for (int j = 0; j < len; j += h) {
				Complex w(1, 0);
				for (int k = j; k < j + h / 2; ++k) {
					Complex u = y[k];
					Complex t = w * y[k + h / 2];
					y[k] = u + t;
					y[k + h / 2] = u - t;
					w = w * wn;
				}
			}
		}
		if (on == -1) {
			for (int i = 0; i < len; ++i) 
				y[i].x /= len;
		}
	}
}fft; 

struct node{
	int v, id;
	bool operator < (const node &other) const { return v < other.v; }
}b[M]; 

inline void getComplex(int id, Complex *x) {
	for (int i = 1; i <= n; ++i) ++num[a[id][i]];
	for (int i = 0; i < len; ++i) x[i] = Complex(num[i]);
	for (int i = 1; i <= n; ++i) --num[a[id][i]];
}

ll gao(int id) {
	int id1 = (id + 1) % 3;
	int id2 = (id1 + 1) % 3;
	getComplex(id1, x1);
	getComplex(id2, x2);
	fft.gao(x1, len, 1);
	fft.gao(x2, len, 1);
	for (int i = 0; i < len; ++i) x1[i] = x1[i] * x2[i];
	fft.gao(x1, len, -1);
	sum[0] = 0;
	for (int i = 1; i <= len; ++i) sum[i] = sum[i - 1] + ll(x1[i].x + 0.5);	
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += sum[len] - sum[a[id][i] - 1];  
	return ans;
}

ll gao_fft() {
	ll ans = 0;
	for (int i = 0; i < 3; ++i) ans += gao(i);
	cnt[0] = cnt[1] = cnt[2] = 0;
	for (int i = 1; i <= tot; ++i) {
		int id = b[i].id;
		int id1 = (id + 1) % 3;
		int id2 = (id1 + 1) % 3;
		ans -= 1ll * (n - cnt[id1]) * cnt[id2];
		ans -= 1ll * (n - cnt[id2]) * cnt[id1];
		ans -= 1ll * (n - cnt[id1]) * (n - cnt[id2]);
		++cnt[id];
	}
	return ans;
}

ll gao_n2() {
	cnt[0] = cnt[1] = cnt[2] = 0;
	ll ans = 0;
	for (int i = 1; i <= tot; ++i) {
		int id = b[i].id;
		int id1 = (id + 1) % 3;
	   	int id2 = (id1 + 1) % 3;
		int pos = cnt[id2];
		for (int j = 1; j <= cnt[id1]; ++j) {
			while (pos > 0 && a[id1][j] + a[id2][pos] >= b[i].v) --pos;
			ans += cnt[id2] - pos;
		}	
		++cnt[id]; 
	}
	return ans;
}

int main() {
	memset(num, 0, sizeof num);
	len = 1;
	while (len < 200000) len <<= 1;
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		for (int i = 0; i < 3; ++i) 
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);
		for (int i = 0; i < 3; ++i) sort(a[i] + 1, a[i] + 1 + n);
		tot = 0;
		for (int i = 0; i < 3; ++i)
			for (int j = 1; j <= n; ++j)
				b[++tot] = {a[i][j], i};
		sort(b + 1, b + 1 + tot);
		ll ans;
		if (n <= 1000) ans = gao_n2();
	    else ans = gao_fft();
		printf("%lld\n", ans); 	
	}
	return 0;
}

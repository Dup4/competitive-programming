#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
const db PI = acos(-1.0);
const int N = 3e6 + 10;
int n, m, a[N], b[N], sum[N];
struct Complex {
	db x, y;
	Complex(db _x = 0.0, db _y = 0.0) { x = _x, y = _y; }
	Complex operator - (const Complex &b) const { return Complex(x - b.x, y - b.y); }
	Complex operator + (const Complex &b) const { return Complex(x + b.x, y + b.y); }
	Complex operator * (const Complex &b) const { return Complex(x * b.x - y * b.y, x * b.y + y * b.x); }
}x1[N], x2[N]; 
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

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i <= n; ++i) scanf("%d", a + i);
		for (int i = 0; i <= m; ++i) scanf("%d", b + i);
		int len = 1;
		while (len < n * 2 || len < m * 2) len <<= 1;
		for (int i = 0; i < len; ++i) {
			x1[i] = Complex(0, 0);
			x2[i] = Complex(0, 0);
		}
		for (int i = 0; i <= n; ++i) {
			x1[i] = Complex(a[i], 0);
		}
		for (int i = 0; i <= m; ++i) {
			x2[i] = Complex(b[i], 0);
		}
		fft.gao(x1, len, 1);
		fft.gao(x2, len, 1);
		for (int i = 0; i < len; ++i) 
			x1[i] = x1[i] * x2[i];
		fft.gao(x1, len, -1);
		for (int i = 0; i < len; ++i) 
			sum[i] = (int)(x1[i].x + 0.5);
		for (int i = 0; i <= n + m; ++i)
			printf("%d%c", sum[i], " \n"[i == n + m]);
	}
	return 0;
}

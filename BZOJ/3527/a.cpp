#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
const double PI = acos(-1.0);
struct Complex {
	double x, y;
	Complex(double _x = 0.0, double _y = 0.0) {
		x = _x;
		y = _y;
	}
	Complex operator - (const Complex &b) const {
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex &b) const {
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex &b) const {
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};
void change(Complex *y, int len) {
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; ++i) {
		if (i < j) {
			swap(y[i], y[j]);
		}
		k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) {
			j += k;
		}
	}
}
void fft(Complex *y, int len, int on) {
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
		for (int i = 0; i < len; ++i) {
			y[i].x /= len;
		}
	}
}

#define db double
#define N 500010
int n, m;
Complex x1[N], x2[N];
db a[N], b[N], res[N];

void work(db *a, db *b) {
	int len = 1;
	while (len < n * 2) {
		len <<= 1;
	}
	for (int i = 0; i < len; ++i) {
		x1[i] = x2[i] = Complex(0, 0);
	}
	for (int i = 0; i < n; ++i) {
		x1[i] = Complex(a[i + 1], 0);
		x2[i] = Complex(b[i + 1], 0);
	}
	fft(x1, len, 1);
	fft(x2, len, 1);
	for (int i = 0; i < len; ++i) {
		x1[i] = x1[i] * x2[i];
	}
	fft(x1, len, -1);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lf", a + i);
			b[i] = 1.0 / i / i; 
		}
		work(a, b);
		for (int i = 2; i <= n; ++i) {
			res[i] = x1[i - 2].x;
		}
		reverse(a + 1, a + 1 + n);
		work(a, b);
		for (int i = n - 1; i >= 1; --i) {
			res[i] -= x1[n - i - 1].x;
		}
		for (int i = 1; i <= n; ++i) {
			printf("%.10f\n", res[i]);
		}
	}
	return 0;
}

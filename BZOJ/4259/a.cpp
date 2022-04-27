#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const db PI = acos(-1.0);
const db eps = 1e-8;
const int N = 1e6 + 10;
char s[N], t[N];
int n, m, a[N], b[N];
db f[N];
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
struct Complex {
    db x, y;
    Complex(db _x = 0.0, db _y = 0.0) {
        x = _x, y = _y;
    }
    Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
} x1[N], x2[N];
struct FFT {
    //进行FFT和IFFT的反转变换
    //位置i和(i 二进制反转后位置)互转
    // len 必须为2的幂次
    void change(Complex *y, int len) {
        int i, j, k;
        for (i = 1, j = len / 2; i < len - 1; ++i) {
            if (i < j)
                swap(y[i], y[j]);
            //交换互为下标反转的元素 i < j 保证交换一次
            // i 做正常的 + 1 j 做反转类型的 + 1 始终保持i 和 j 是反转的
            k = len / 2;
            while (j >= k) {
                j -= k;
                k /= 2;
            }
            if (j < k)
                j += k;
        }
    }
    // on = 1 DFT
    // on = -1 IDFT
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
            for (int i = 0; i < len; ++i) y[i].x /= len;
        }
    }
} fft;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        scanf("%s%s", s, t);
        reverse(s, s + n);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '*')
                a[i] = 0;
            else
                a[i] = s[i] - 'a' + 1;
        }
        for (int i = 0; i < m; ++i) {
            if (t[i] == '*')
                b[i] = 0;
            else
                b[i] = t[i] - 'a' + 1;
        }

        int len = 1;
        while (len < n + m) len <<= 1;

        for (int i = 0; i < len; ++i) x1[i] = x2[i] = Complex(0.0, 0.0);
        for (int i = 0; i < n; ++i) x1[i] = Complex(1ll * a[i] * a[i] * a[i], 0.0);
        for (int i = 0; i < m; ++i) x2[i] = Complex(1ll * b[i], 0.0);
        fft.gao(x1, len, 1);
        fft.gao(x2, len, 1);
        for (int i = 0; i < len; ++i) x1[i] = x1[i] * x2[i];
        fft.gao(x1, len, -1);
        for (int i = 0; i < m; ++i) f[i] += x1[i].x;

        for (int i = 0; i < len; ++i) x1[i] = x2[i] = Complex(0.0, 0.0);
        for (int i = 0; i < n; ++i) x1[i] = Complex(1ll * a[i], 0.0);
        for (int i = 0; i < m; ++i) x2[i] = Complex(1ll * b[i] * b[i] * b[i], 0.0);
        fft.gao(x1, len, 1);
        fft.gao(x2, len, 1);
        for (int i = 0; i < len; ++i) x1[i] = x1[i] * x2[i];
        fft.gao(x1, len, -1);
        for (int i = 0; i < m; ++i) f[i] += x1[i].x;

        for (int i = 0; i < len; ++i) x1[i] = x2[i] = Complex(0.0, 0.0);
        for (int i = 0; i < n; ++i) x1[i] = Complex(1ll * a[i] * a[i], 0.0);
        for (int i = 0; i < m; ++i) x2[i] = Complex(1ll * b[i] * b[i], 0.0);
        fft.gao(x1, len, 1);
        fft.gao(x2, len, 1);
        for (int i = 0; i < len; ++i) x1[i] = x1[i] * x2[i];
        fft.gao(x1, len, -1);
        for (int i = 0; i < m; ++i) f[i] += -2.0 * x1[i].x;

        vector<int> res;
        for (int i = n - 1; i < m; ++i)
            if (int(f[i] + 0.2) == 0)
                res.push_back(i - (n - 1) + 1);
        int sze = res.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) printf("%d%c", res[i], " \n"[i == sze - 1]);
    }
    return 0;
}

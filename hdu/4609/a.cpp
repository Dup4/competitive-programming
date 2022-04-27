#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
const db PI = acos(-1.0);
const int N = 4e5 + 10;
int n;
ll a[N], sum[N];
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
} x[N];
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
inline ll tot(ll x) {
    return x * (x - 1) * (x - 2) / 6;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        memset(sum, 0, sizeof sum);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
            ++sum[a[i]];
        }
        int len = 1;
        while (len < 200000) len <<= 1;
        for (int i = 0; i < len; ++i) {
            x[i] = Complex(sum[i]);
        }
        fft.gao(x, len, 1);
        for (int i = 0; i < len; ++i) x[i] = x[i] * x[i];
        fft.gao(x, len, -1);
        for (int i = 0; i < len; ++i) sum[i] = (long long)(x[i].x + 0.5);
        //减去自己和自己的组合
        for (int i = 1; i <= n; ++i) --sum[a[i] + a[i]];
        //组合是无序的，所有每种方案都除2
        for (int i = 0; i < len; ++i) sum[i] /= 2;
        //求前缀和
        for (int i = 0; i <= len; ++i) sum[i] += sum[i - 1];
        ll res = 0;
        sort(a + 1, a + 1 + n);
        //枚举最大的
        for (int i = 1; i <= n; ++i) {
            res += sum[len] - sum[a[i]];
            //减去取自己的方案
            res -= n - 1;
            //减去取一大一小的方案
            res -= 1ll * (i - 1) * (n - i);
            //减去取两个大的
            res -= 1ll * (n - i) * (n - i - 1) / 2;
        }
        printf("%.7f\n", res * 1.0 / tot(n));
    }
    return 0;
}

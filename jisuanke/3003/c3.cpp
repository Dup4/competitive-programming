#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
struct Complex {
    double r, i;
    Complex(double _r = 0, double _i = 0) {
        r = _r;
        i = _i;
    }
    Complex operator+(const Complex &b) {
        return Complex(r + b.r, i + b.i);
    }
    Complex operator-(const Complex &b) {
        return Complex(r - b.r, i - b.i);
    }
    Complex operator*(const Complex &b) {
        return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
};
void change(Complex y[], int len) {
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j)
            swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k)
            j += k;
    }
}
void fft(Complex y[], int len, int on) {
    change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1)
        for (int i = 0; i < len; i++) y[i].r /= len;
}

const int MAXN = 100010;
Complex x1[MAXN * 4];
Complex x2[MAXN * 4];
int a[3][MAXN];
long long num[MAXN * 4];
long long sum[MAXN * 4];

long long gao(int id, int n) {
    int id1 = (id + 1) % 3;
    int id2 = (id + 2) % 3;
    int len1 = 0;
    for (int i = 0; i < n; i++) {
        num[a[id1][i]]++;
        len1 = max(len1, a[id1][i] + 1);
        len1 = max(len1, a[id2][i] + 1);
    }
    int len = 1;
    while (len < 2 * len1) len <<= 1;
    for (int i = 0; i < len1; i++) x1[i] = Complex(num[i], 0);
    for (int i = len1; i < len; i++) x1[i] = Complex(0, 0);
    fft(x1, len, 1);
    for (int i = 0; i < n; i++) num[a[id1][i]]--;
    for (int i = 0; i < n; i++) num[a[id2][i]]++;
    for (int i = 0; i < len1; i++) x2[i] = Complex(num[i], 0);
    for (int i = len1; i < len; i++) x2[i] = Complex(0, 0);
    fft(x2, len, 1);

    for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
    fft(x1, len, -1);
    for (int i = 0; i < len; i++) num[i] = (long long)(x1[i].r + 0.5);
    sum[0] = 0;
    for (int i = 1; i <= 2 * len1; i++) sum[i] = sum[i - 1] + num[i];
    for (int i = 0; i < len; i++) num[i] = 0;

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += sum[2 * len1] - sum[a[id][i] - 1];
    }
    return ans;
}

struct Node {
    int v;
    int id;
} node[MAXN * 3];
bool cmp(Node A, Node B) {
    return A.v < B.v;
}

long long gao_fft(int n) {
    long long ans = 0;
    ans += gao(0, n);
    ans += gao(1, n);
    ans += gao(2, n);
    for (int i = 0; i < n; i++) {
        node[i].v = a[0][i];
        node[i].id = 0;
    }
    for (int i = n; i < 2 * n; i++) {
        node[i].v = a[1][i - n];
        node[i].id = 1;
    }
    for (int i = 2 * n; i < 3 * n; i++) {
        node[i].v = a[2][i - 2 * n];
        node[i].id = 2;
    }
    sort(node, node + 3 * n, cmp);
    int cnt[3];
    cnt[0] = cnt[1] = cnt[2] = 0;
    for (int i = 0; i < 3 * n; i++) {
        int id = node[i].id;
        int id1 = (id + 1) % 3;
        int id2 = (id + 2) % 3;
        ans -= (long long)(n - cnt[id1]) * cnt[id2];
        ans -= (long long)(n - cnt[id2]) * cnt[id1];
        ans -= (long long)(n - cnt[id1]) * (n - cnt[id2]);
        cnt[id]++;
    }
    return ans;
}

long long gao_n2(int n) {
    sort(a[0], a[0] + n);
    sort(a[1], a[1] + n);
    sort(a[2], a[2] + n);
    for (int i = 0; i < n; i++) {
        node[i].v = a[0][i];
        node[i].id = 0;
    }
    for (int i = n; i < 2 * n; i++) {
        node[i].v = a[1][i - n];
        node[i].id = 1;
    }
    for (int i = 2 * n; i < 3 * n; i++) {
        node[i].v = a[2][i - 2 * n];
        node[i].id = 2;
    }
    sort(node, node + 3 * n, cmp);
    int cnt[3];
    cnt[0] = cnt[1] = cnt[2] = 0;
    long long ans = 0;
    for (int i = 0; i < 3 * n; i++) {
        int id = node[i].id;
        int id1 = (id + 1) % 3;
        int id2 = (id + 2) % 3;
        int tmp = cnt[id2];
        for (int j = 0; j < cnt[id1]; j++) {
            while (tmp > 0 && a[id1][j] + a[id2][tmp - 1] >= node[i].v) tmp--;
            ans += cnt[id2] - tmp;
        }
        cnt[id]++;
    }
    return ans;
}

int main() {
    int T;
    int n;
    scanf("%d", &T);
    int iCase = 0;
    while (T--) {
        scanf("%d", &n);
        iCase++;
        for (int i = 0; i < n; i++) scanf("%d", &a[0][i]);
        for (int i = 0; i < n; i++) scanf("%d", &a[1][i]);
        for (int i = 0; i < n; i++) scanf("%d", &a[2][i]);

        long long ans;
        if (n <= 2000)
            ans = gao_n2(n);
        else
            ans = gao_fft(n);
        ans = gao_fft(n);
        printf("Case #%d: ", iCase);
        cout << ans << endl;
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int s[N], n, k;
struct DA {
    //求SA数组需要用到的中间变量，不需要赋值
    int t1[N], t2[N], c[N];
    int sa[N];
    int Rank[N];
    int height[N];
    //待排序的字符串放在str数组中，从str[0] - s[n - 1]长度为n, 最大值小于m
    int str[N];
    int n, m;
    void init(int *s, int m, int n) {
        this->m = m;
        this->n = n;
        for (int i = 0; i < n; ++i) str[i] = s[i];
        str[n] = 0;
    }
    bool cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    void work() {
        ++n;
        int i, j, p, *x = t1, *y = t2;
        //第一轮基数排序，如果s的最大值很大，可改为快速排序
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[i] = str[i]]++;
        for (i = 1; i < m; ++i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (j = 1; j <= n; j <<= 1) {
            p = 0;
            //直接利用sa数组排序第二关键字
            //后面的j个数第二关键字为空的最小
            for (i = n - j; i < n; ++i) {
                y[p++] = i;
            }
            for (i = 0; i < n; ++i)
                if (sa[i] >= j)
                    y[p++] = sa[i] - j;
            //这样数组y保存的就是按照第二关键字排序的结果
            //基数排序第一关键字
            for (i = 0; i < m; ++i) c[i] = 0;
            for (i = 0; i < n; ++i) c[x[y[i]]]++;
            for (i = 1; i < m; ++i) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            //根据sa和x数组计算新的x数组
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; ++i) {
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
            }
            if (p >= n)
                break;
            //下次基数排序的最大值
            m = p;
        }
        int k = 0;
        --n;
        for (i = 0; i <= n; ++i) Rank[sa[i]] = i;
        // build height
        for (i = 0; i < n; ++i) {
            if (k)
                --k;
            j = sa[Rank[i] - 1];
            while (str[i + k] == str[j + k]) ++k;
            height[Rank[i]] = k;
        }
    }
} da;

bool check(int x) {
    int cnt = 1;
    for (int i = 2; i <= n; ++i) {
        if (da.height[i] >= x) {
            ++cnt;
        } else {
            cnt = 1;
        }
        if (cnt >= k)
            return 1;
    }
    return 0;
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 0; i < n; ++i) scanf("%d", s + i);
        da.init(s, 1000000, n);
        da.work();
        int l = 1, r = n, res = -1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

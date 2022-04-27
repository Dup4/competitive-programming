#include <bits/stdc++.h>
using namespace std;

struct node {
    int a[2][2];
    node() {
        memset(a, 0, sizeof a);
    }
    void set() {
        a[0][0] = a[1][1] = 1;
    }
    bool isbase() {
        return a[0][0] == 1 && a[0][1] == 0 && a[1][0] == 0 && a[1][1] == 1;
    }
    node operator*(const node &other) const {
        node res = node();
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    res.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return res;
    }
} base, res, tmp;
node qmod(node base, int n) {
    node res = node();
    res.set();
    while (n) {
        if (n & 1) {
            res = res * base;
        }
        base = base * base;
        n >>= 1;
    }
    return res;
}

bool ok(int n) {
    for (int i = 2; i < n; ++i) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    vector<int> vec;
    for (int i = 3; i <= 100; ++i) {
        if (ok(i)) {
            vec.push_back(i);
        }
    }
    for (int i = -100; i <= 100; ++i) {
        for (int j = -100; j <= 100; ++j) {
            for (int k = -100; k <= 100; ++k) {
                for (int l = -100; l <= 100; ++l) {
                    base = node();
                    base.a[0][0] = i;
                    base.a[0][1] = j;
                    base.a[1][0] = k;
                    base.a[1][1] = l;
                    tmp = base;
                    for (auto it : vec) {
                        res = qmod(base, it);
                        if (res.isbase()) {
                            printf("%d\n", it);
                            for (int _i = 0; _i < 2; ++_i) {
                                for (int _j = 0; _j < 2; ++_j) {
                                    printf("%d ", tmp.a[i][j]);
                                }
                                puts("");
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

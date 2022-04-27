#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        vector<int> res;
        int last = -1;
        int l = 1, r = n;
        while (1) {
            if (l == r) {
                if (a[l] > last) {
                    res.push_back(0);
                }
                break;
            }
            if (max(a[l], a[r]) <= last) {
                break;
            }
            if (a[l] == a[r]) {
                int cl = 0, cr = 0;
                int t = last;
                for (int i = l; i <= r; ++i) {
                    if (a[i] <= t) {
                        break;
                    }
                    t = a[i];
                    ++cl;
                }
                t = last;
                for (int i = r; i >= l; --i) {
                    if (a[i] <= t) {
                        break;
                    }
                    t = a[i];
                    ++cr;
                }
                if (cl >= cr) {
                    for (int i = l; i <= r; ++i) {
                        if (a[i] <= last) {
                            break;
                        }
                        last = a[i];
                        res.push_back(0);
                    }
                } else {
                    for (int i = r; i >= l; --i) {
                        if (a[i] <= last) {
                            break;
                        }
                        last = a[i];
                        res.push_back(1);
                    }
                }
            } else if (min(a[l], a[r]) > last) {
                if (a[l] < a[r]) {
                    res.push_back(0);
                    last = a[l];
                    ++l;
                } else {
                    res.push_back(1);
                    last = a[r];
                    --r;
                }
            } else if (a[l] > last) {
                res.push_back(0);
                last = a[l];
                ++l;
            } else {
                res.push_back(1);
                last = a[r];
                --r;
            }
        }
        printf("%d\n", int(res.size()));
        for (auto it : res) {
            putchar(it ? 'R' : 'L');
        }
        puts("");
    }
    return 0;
}

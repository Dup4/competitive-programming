#include <bits/stdc++.h>
using namespace std;

#define N 300010
char s[N];
int n, l, spa, r;
void print() {
    puts(":(");
}
bool ok() {
    int l = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(') {
            ++l;
        } else {
            --l;
            if (i != n && l <= 0) {
                return false;
            }
        }
    }
    return l == 0;
}
void solve() {
    for (int i = n; i >= 1; --i) {
        if (s[i] == '(') {
            --r;
            --l;
            if (r < 0 || (i != 1 && r == 0)) {
                print();
                return;
            }
        } else if (s[i] == ')') {
            ++r;
            if (i != n && spa + l <= r) {
                print();
                return;
            }
        } else {
            if (2 * (spa + l) - i > r) {
                ++r;
                s[i] = ')';
            } else if (r > 0) {
                s[i] = '(';
                --r;
                if (i != 1 && r == 0) {
                    print();
                    return;
                }
            } else {
                print();
                return;
            }
            --spa;
        }
    }
    if (l > 0 || r > 0) {
        print();
        return;
    } else {
        printf("%s\n", s + 1);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        l = 0, spa = 0, r = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '(') {
                ++l;
            } else if (s[i] == '?') {
                ++spa;
            }
        }
        solve();
    }
    return 0;
}

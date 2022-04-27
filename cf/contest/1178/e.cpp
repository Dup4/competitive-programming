#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, f[N][3], g[N][3], nx[3];
char s[N];
struct node {
    int pre, x, y;
    node() {}
    node(int pre, int x, int y) : pre(pre), x(x), y(y) {}
    bool operator>(const node &other) const {
        if (x != other.x)
            return x > other.x;
        return y > other.y;
    }
} g[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        nx[0] = nx[1] = nx[2] = 0;
        for (int i = 1; i <= n + 1; ++i) {
            for (int j = 0; j < 3; ++j) {
                f[i][j] = nx[j];
            }
            if (i <= n) {
                nx[s[i] - 'a'] = i;
            }
        }
        node Min = node(0, 0, n + 1);
        for (int i = 1; i <= n; ++i) {
        }
    }
    return 0;
}

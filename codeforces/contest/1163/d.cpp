#include <bits/stdc++.h>
using namespace std;

#define N 1010
char c[N], s[N], t[N];
int len, lens, lent;
bool ok(int x) {
    for (int i = x, j = 1; j <= lens; ++i, ++j) {
        if (c[i] != '*' && c[i] != s[j]) {
            return false;
        }
    }
    return true;
}
int g() {
    int res = 0;
    for (int i = 1; i + lent - 1 <= len; ++i) {
        bool flag = 1;
        for (int j = i, k = 1; k <= lent; ++j, ++k) {
            if (c[j] != t[k]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            ++res;
        }
    }
    return res;
}

int main() {
    srand(time(NULL));
    while (scanf("%s", c + 1) != EOF) {
        scanf("%s", s + 1);
        scanf("%s", t + 1);
        len = strlen(c + 1);
        lens = strlen(s + 1);
        lent = strlen(t + 1);
        vector<int> vec;
        for (int i = 1; i <= len; ++i) {
            if (c[i] == '*') {
                vec.push_back(i);
            }
        }
        int ans = -1e9;
        for (int _ = 1; _ <= 6000; ++_) {
            for (auto it : vec) {
                char x = 'a' + rand() % 26;
                c[it] = x;
            }
            int res = 0;
            for (int i = 1; i + lens - 1 <= len; ++i) {
                if (ok(i)) {
                    ++res;
                }
            }
            res -= g();
            ans = max(ans, res);
        }
        printf("%d\n", ans);
    }
    return 0;
}

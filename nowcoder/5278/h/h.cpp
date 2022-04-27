#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
const int N = 1e5 + 10;
char s[N];
int n, k, cnt[20];

int sum, tmp;

void chmax(int &x, int y) {
    if (x < y)
        x = y;
}

void dfs(int cur, int num, int modsum, int pre) {
    if (cur == k) {
        if ((sum + modsum) % 3 == 0) {
            chmax(tmp, num);
        }
        return;
    }
    for (int i = pre; i >= 0; --i) {
        if (cnt[i]) {
            --cnt[i];
            dfs(cur + 1, num * 10 + i, modsum + i, i);
            ++cnt[i];
        }
    }
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        memset(cnt, 0, sizeof cnt);
        scanf("%s%d", s + 1, &k);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) ++cnt[s[i] - '0'];
        vector<int> vec;
        int need = k;
        sum = 0;
        tmp = -1;
        for (int i = 9; i >= 0; --i) {
            while (need > 4 && cnt[i]) {
                --need;
                --cnt[i];
                sum = (sum + i) % 3;
                vec.push_back(i);
            }
        }
        if (k > 4)
            k = 4;
        dfs(0, 0, 0, 9);
        if (tmp != -1) {
            for (int i = 0; i < k; ++i) {
                vec.push_back(tmp % 10);
                tmp /= 10;
            }
            sort(vec.begin(), vec.end(), [&](int x, int y) {
                return x > y;
            });
            if (vec[0] == 0 && SZ(vec) > 1)
                puts("-1");
            else {
                for (int i = 0; i < SZ(vec); ++i) printf("%d", vec[i]);
                puts("");
            }
        } else {
            puts("-1");
        }
    }
    return 0;
}

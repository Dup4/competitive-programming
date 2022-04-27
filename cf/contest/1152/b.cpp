#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    while (scanf("%d", &x) != EOF) {
        vector<int> res;
        while (x != 1) {
            int t = x;
            int r = 0;
            int cnt = 0;
            while (t) {
                ++r;
                cnt += t % 2;
                t /= 2;
            }
            if (cnt == 1) {
                res.push_back(0);
                ++x;
                continue;
            }
            res.push_back(r);
            x ^= ((1 << (r)) - 1);
            ++x;
        }
        int sze = (int)res.size();
        printf("%d\n", sze * 2);
        for (int i = 0; i < sze; ++i) {
            printf("%d%c", res[i], " \n"[i == sze - 1]);
        }
    }
    return 0;
}

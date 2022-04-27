#include <bits/stdc++.h>
using namespace std;

int n, m;
int get(int x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        m = get(n);
        vector<int> vec;
        for (int i = 1; i <= m; ++i) {
            if (m % i == 0 && n % i == 0) {
                vec.push_back(i);
            }
        }
        int sze = (int)vec.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) printf("%d%c", vec[i], " \n"[i == sze - 1]);
    }
    return 0;
}

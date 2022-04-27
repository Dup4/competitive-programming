#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;
int f(int x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    vector<int> vec;
    for (int i = 1; i <= 1000; ++i) {
        if (f(i) == i / 2) {
            vec.push_back(i);
        }
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        int res = 0;
        for (auto it : vec) {
            if (n % it == 0) {
                ++res;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

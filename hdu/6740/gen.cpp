#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
    printf("%lld %lld\n", rnd(), rnd());
    int n = 1e7;
    for (int i = 1; i <= n; ++i) {
        printf("%c", rnd() % 26 + 'a');
    }
    cout << endl;
    return 0;
}

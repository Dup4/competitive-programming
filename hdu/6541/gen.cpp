#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int main() {
    int limit = 100000;
    int n = random(1, limit), m = random(1, limit);
    cout << n << " " << m << endl;
    for (int i = 1; i <= n + m; ++i) printf("%d %d\n", random(1, limit), random(1, limit));
    return 0;
}

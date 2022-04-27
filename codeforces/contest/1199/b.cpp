#include <bits/stdc++.h>
using namespace std;

#define db double

int main() {
    db H, L;
    while (cin >> H >> L) {
        printf("%.16f\n", (L * L - H * H) * 1.0 / (2 * H));
    }
    return 0;
}

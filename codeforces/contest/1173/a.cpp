#include <bits/stdc++.h>
using namespace std;

int x, y, z;

int work1() {
    return x + z > y;
}

int work2() {
    return (z >= abs(x - y) && (z - abs(x - y)) % 2 == 0);
}

int work3() {
    return y + z > x;
}

int main() {
    while (scanf("%d%d%d", &x, &y, &z) != EOF) {
        if (work1() + work2() + work3() >= 2) {
            puts("?");
        } else if (work1()) {
            puts("+");
        } else if (work2()) {
            puts("0");
        } else {
            puts("-");
        }
    }
    return 0;
}

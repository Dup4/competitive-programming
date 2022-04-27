#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int main() {
    int x1 = 3, y1 = 1;
    int x2 = x1, y2 = y1, x3, y3;
    for (int i = 1; i <= 10; i++) {
        x3 = x2 * x1 + 8 * y2 * y1;
        y3 = x2 * y1 + y2 * x1;
        x2 = x3, y2 = y3;
        printf("%10d%10d\n", y3, (x3 - 1) / 2);
    }
    return 0;
}

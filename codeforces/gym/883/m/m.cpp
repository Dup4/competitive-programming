#include <bits/stdc++.h>
using namespace std;

int x[2], y[2];

int dis(int x, int y, int x1, int y1) {
    return abs(x - x1) + abs(y - y1);
}

int main() {
    scanf("%d%d%d%d", x, y, x + 1, y + 1);
    int Dis = dis(x[0], y[0], x[1], y[1]);
    if (x[0] == x[1] || y[0] == y[1])
        printf("%d\n", Dis * 2 + 6);
    else
        printf("%d\n", Dis * 2 + 4);
    return 0;
}

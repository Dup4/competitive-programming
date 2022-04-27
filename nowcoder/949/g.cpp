#include <bits/stdc++.h>
using namespace std;

#define db double
const db PI = acos(-1.0);

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%.3f\n", n * n * 1.0 / 2 / PI);
    }
    return 0;
}

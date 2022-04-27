#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    while (scanf("%02d%02d", &a, &b) != EOF) {
        if (a >= 1 && a <= 12 && b >= 1 && b <= 12) {
            puts("AMBIGUOUS");
        } else if (a >= 1 && a <= 12) {
            puts("MMYY");
        } else if (b >= 1 && b <= 12) {
            puts("YYMM");
        } else {
            puts("NA");
        }
    }
    return 0;
}

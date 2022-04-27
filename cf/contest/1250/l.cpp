#include <bits/stdc++.h>
using namespace std;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int res = max((a + b + c + 2) / 3, min(a, c));
        printf("%d\n", res);
        //		if (a > c) swap(a, c);
    }
    return 0;
}

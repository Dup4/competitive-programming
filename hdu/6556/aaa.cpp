#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 0; i < 24; ++i) {
        int h = (i - 1 + 12) % 12 + 1;
        int t = i;
        if (t >= 12)
            t -= 12;
        if (t == 0)
            t = 12;
        printf("%d %d\n", h, t);
    }
}

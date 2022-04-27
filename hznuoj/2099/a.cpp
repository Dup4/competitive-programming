#include <bits/stdc++.h>
using namespace std;

//返回值[0, 6]表示星期天~星期六
int getweek(int y, int m, int d) {
    if (m < 3) {
        y -= 1;
        m += 12;
    }
    int c = y / 100;
    y = y - 100 * c;
    return ((y + y / 4 + c / 4 - 2 * c + (13 * (m + 1)) / 5 + d - 1) % 7 + 7) % 7;
}

//返回值[1, 7],表示星期一~星期天
int getweek2(int y, int m, int d) {
    int ans;
    if (m == 1 || m == 2)
        m += 12, y--;
    if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
    } else {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    }
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return ans + 1;
}

int main() {
    char *w[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int y, m, d;
    while (cin >> y >> m >> d) {
        cout << w[getweek(y, m, d) % 7] << endl;
        cout << w[getweek2(y, m, d) % 7] << endl;
    }
    return 0;
}

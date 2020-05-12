#include <bits/stdc++.h>
using namespace std;

struct node {
	int y, m, d;
	node(int y = 0, int m = 0, int d = 0) : y(y), m(m), d(d) {}
	bool operator < (const node &other) const {
		if (y != other.y)
			return y < other.y;
		if (m != other.m)
			return m < other.m;
		return d < other.d; 
	}
	bool operator == (const node &other) const { 
		return y == other.y && m == other.m && d == other.d;
	}
};

int getweek(int y, int m, int d) {
    int ans;
    if (m == 1 || m == 2) m += 12, y--;
    if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
    } else {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    }
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return ans + 1;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int y, m, d;
		scanf("%d%d%d", &y, &m, &d);
		node A = node(y, m, d);
		vector <node> vec[2];
		for (int i = y; i <= y + 1; ++i) {
			for (int j = 1, cnt = 0; j <= 31; ++j) {
				if (getweek(i, 5, j) == 7) {
					++cnt;
					if (cnt == 2) {
						vec[0].emplace_back(i, 5, j);
						break;
					}
				}
			}
			for (int j = 1, cnt = 0; j <= 30; ++j) {
				if (getweek(i, 6, j) == 7) {
					++cnt;
					if (cnt == 3) {
						vec[1].emplace_back(i, 6, j);
						break;
					}
				}
			}
		}
		node B = node();;
		int flag = -1;
		for (auto &it : vec[0]) {
			if (!(A == it) && A < it) {
				if (flag == -1) {
					flag = 0;
					B = it;
				} else if (it < B) {
					flag = 0;
					B = it;
				}
			}
		}
		for (auto &it : vec[1]) {
			if (!(A == it) && A < it) {
				if (flag == -1) {
					flag = 1;
					B = it;
				} else if (it < B) {
					flag = 1;
					B = it;
				}
			}
		}
		if (!flag) printf("Mother's Day: May ");
		else printf("Father's Day: June ");
		string s = "th";
		if (B.d == 1 || B.d == 21 || B.d == 31) s = "st";
		if (B.d == 2 || B.d == 22 || B.d == 32) s = "nd";
		if (B.d == 3 || B.d == 23 || B.d == 33) s = "rd";
		cout << B.d << s << ", " << B.y << "\n";
	}	
	return 0;
}

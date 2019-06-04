
#include <algorithm>
/* 请在下面编写isPalindrome函数 */
bool isPalindrome(const vector <int> &v) {
	string res = "";
	for (auto it : v) {
		res += it - '0';
	}
	string t = res;
	reverse(res.begin(), res.end());
	return t == res;
}

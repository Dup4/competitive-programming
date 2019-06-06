#include <iostream>
using namespace std;
int sumDigits(int n);
int main() {
    int n;
    cin >> n;
    cout << sumDigits(n) << endl;
    return 0;
}
/* 请在下面编写sumDigits函数 */
int sumDigits(int n) {
	int res = 0;
	while (n) {
		res += n % 10;
		n /= 10;
	}
	return res;
}

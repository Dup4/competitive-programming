#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
	unsigned int x = 8;
	//返回x的最后一位1是从低位向高位第几位的 
	cout << __builtin_ffs(x) << endl;
	//返回前导的0的个数
	cout << __builtin_clz(x) << endl;
	//返回后面的0的个数
	cout << __builtin_ctz(x) << endl;
	//返回二进制表示中1的个数
	cout << __builtin_popcount(x) << endl;
	//返回x的奇偶校验位，也就是x的1的个数模2的结果
	cout << __builtin_parity(x) << endl;
	
	unsigned long long y = 8;
	//返回x的最后一位1是从低位向高位第几位的 
	cout << __builtin_ffsll(y) << endl;
	//返回前导的0的个数
	cout << __builtin_clzll(y) << endl;
	//返回后面的0的个数
	cout << __builtin_ctzll(y) << endl;
	//返回二进制表示中1的个数
	cout << __builtin_popcountll(y) << endl;
	//返回x的奇偶校验位，也就是x的1的个数模2的结果
	cout << __builtin_parityll(y) << endl;
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int count_bits(int x) {
  int xx = x;
  xx = xx - ((xx >> 1) & 0x55555555);
  xx = (xx & 0x33333333) + ((xx >> 2) & 0x33333333);
  xx = (xx + (xx >> 4)) & 0x0f0f0f0f;
  xx = xx + (xx >> 8);
  return (xx + (xx >> 16)) & 0xff;
}

int count_bits2(int x)
{
	int i = 0;
	int s = 0;
	for(i = 0;i<32;i++)
	{
		if(x&0x01)
			s ++;
		x = x>>1;
	}
	return (s);
}

int count_bits3(int x) {
	return __builtin_popcount(x);
}


int main() {
	int n = 1e9;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		res ^= count_bits(i);
	} 
	cout << res << endl;
	return 0;
}

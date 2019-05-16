#include <bits/stdc++.h>
using namespace std;

#define ll unsigned long long
int main() {
	ll a[3];
	ifstream in;
	in.open("image.jpg", ios::binary);
	in.seekg(12L, ios::beg);
	in.read(reinterpret_cast< char * > (&a[0]), 1);   
	in.seekg(48L, ios::beg);
	in.read(reinterpret_cast< char * >(&a[1]), 1); 
	in.seekg(79L, ios::beg);
	in.read(reinterpret_cast<char *>(&a[2]), 1);
	int res = 192;
//	string ss = "";
//	while (res) {
//		int x = res % 16;
//		res /= 16;
//		if (x  < 10) {
//			ss += x + '0';
//		} else if (x == 10) {
//			ss += 'a';
//		} else if (x == 11) {
//			ss += 'b';
//		} else if (x == 12) {
//			ss += 'c';
//		} else if (x == 13) {
//			ss += 'd';
//		} else if (x == 14) {
//			ss += 'e';
//		} else if (x == 15) {
//			ss += 'f';
//		}
//	}
//	reverse(ss.begin(), ss.end());
//	cout << ss << endl;
	cout << hex << res << endl;	
	return 0;
}

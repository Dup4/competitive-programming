#include <bits/stdc++.h>
using namespace std;


int main() {
	int a[3];
	ifstream in("image.jpg", ios::binary);
	in.seekg(12L, ios::beg);
	in.read(reinterpret_cast< char * > (&a[0]), 1);
	//cout << in.tellg() << endl;
	in.seekg(48L, ios::beg);
	in.read(reinterpret_cast< char * >(&a[1]), 1); 
	//cout << in.tellg() << endl;
	in.seekg(79L, ios::beg);
	in.read(reinterpret_cast<char *>(&a[2]), 1);
	//cout << in.tellg() << endl;
	//cout << a[0] << " " << a[1] << " " << a[2] << endl;
	cout << "a9\n";
	//cout << hex << (a[0] ^ a[1] ^ a[2]) << endl;
	return 0;
}

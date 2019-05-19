#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a, b, c;
	int h = 0;
	a = b = c = 0;
	ifstream in("image.jpg", ios::binary);
	in.seekg(12L);
	in.read(reinterpret_cast<char*>(&a),1);
	in.seekg(48L);
	in.read(reinterpret_cast<char*>(&b),1);
	in.seekg(79L);
	in.read(reinterpret_cast<char*>(&c),1);
	h=a^b^c;
	cout << hex << h << endl;
	return 0;
}

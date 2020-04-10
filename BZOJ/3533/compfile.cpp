#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **args) {
	ifstream in1(args[1]), in2(args[2]);  
	int row = 0;
	string A, B;
	while (in1 >> A && in2 >> B) {
		++row;
		if (A != B) {
			cout << row << endl;
			return 0;
		}
	}
	return 0;
}

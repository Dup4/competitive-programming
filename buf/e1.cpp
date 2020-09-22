#include <bits/stdc++.h>
using namespace std;


class Finder {
public:
    vector <int> vec;
    int Partition(int l, int r, int k) {
//		cout << l << " " << r << " " << k << endl; 
        if (l == r) return vec[l];
        int _l = l, _r = r;
        int pivot = vec[l];
        while (l < r) {
            while (l < r && vec[r] >= pivot) --r;
            vec[l] = vec[r];
            while (l < r && vec[l] <= pivot) ++l;
            vec[r] = vec[l];
        }
        vec[l] = pivot;
        if (l - _l + 1 == k) return vec[l];
        if (l - _l + 1 > k) return Partition(_l, l, k);
        return Partition(l + 1, _r, k - (l - _l + 1));
    }
    int findKth(vector<int> a, int n, int K) {
        // write code here
        vec = a;
        return Partition(0, n - 1, n - K + 1);
    }
};

int main() {
	vector <int> vec({1, 2, 3, 4, 5, 6, 7});
	cout << ((new Finder())->findKth(vec, vec.size(), 1)) << endl;	
	return 0;
}

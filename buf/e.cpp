#include <bits/stdc++.h>
using namespace std;
static int n = 0;

void dfs(int a[], int iLen, int iStart) {
    if (iLen == iStart) {
        for (int i = 0; i < iLen; ++i) {
            cout << a[i] << " \n"[i == iLen - 1];
        }
        n++;
    } else {
        for (int j = iStart; j < iLen; ++j) {
            swap(a[iStart], a[j]);
            dfs(a, iLen, iStart + 1);
            swap(a[iStart], a[j]);
        }
    }
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    dfs(a, sizeof(a) / sizeof(int), 0);
    cout << "total: " << n << endl;
    return 0;
}

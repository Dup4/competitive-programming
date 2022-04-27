#include <iomanip>
#include <iostream>
using namespace std;
struct Person {
    int no;      // 病人的编号
    double num;  // 病人病情严重程度
};
/* 请在下面编写main函数 */

#include <algorithm>
#include <vector>
#define db double

int main() {
    int n;
    db a;
    cin >> n >> a;
    vector<Person> vec;
    Person x;
    for (int i = 1; i <= n; ++i) {
        cin >> x.no >> x.num;
        if (x.num > a) {
            vec.push_back(x);
        }
    }
    if (vec.empty()) {
        cout << "None.\n";
    } else {
        sort(vec.begin(), vec.end(), [&](Person x, Person y) {
            return x.num > y.num;
        });
        for (auto it : vec) {
            cout.width(3);
            cout.fill('0');
            cout << it.no << " ";
            cout << fixed << setprecision(1) << it.num << "\n";
        }
    }
    return 0;
}

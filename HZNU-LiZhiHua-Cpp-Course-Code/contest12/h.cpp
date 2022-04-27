
#include <algorithm>
class MyLess {
public:
    MyLess() {}
    bool operator()(const int x, const int y) const {
        if (x % 10 != y % 10) {
            return x % 10 > y % 10;
        }
        return abs(x) > abs(y);
    }
};

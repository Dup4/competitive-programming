#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;

#include <cstdio>
class Time {
public:
    int h, m, s;
    bool ok(int h = 0, int m = 0, int s = 0) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            return false;
        }
        return true;
    }
    Time(int h = 0, int m = 0, int s = 0) {
        if (!ok(h, m, s)) {
            throw invalid_argument("Invalid argument!");
        }
        this->h = h;
        this->m = m;
        this->s = s;
    }
    void setHour(int h) {
        if (!ok(h, 0, 0)) {
            throw invalid_argument("Invalid argument!");
        }
        this->h = h;
    }
    void setMinute(int m) {
        if (!ok(0, m, 0)) {
            throw invalid_argument("Invalid argument!");
        }
        this->m = m;
    }
    void setSecond(int s) {
        if (!ok(0, 0, s)) {
            throw invalid_argument("Invalid argument!");
        }
        this->s = s;
    }
    int getHour() {
        return h;
    }
    int getMinute() {
        return m;
    }
    int getSecond() {
        return s;
    }
    void setTime(int h, int m, int s) {
        if (!ok(h, m, s)) {
            throw invalid_argument("Invalid argument!");
        }
        this->h = h;
        this->m = m;
        this->s = s;
    }
    void printTime24() {
        printf("%02d:%02d:%02d\n", h, m, s);
    }
    void printTime12() {
        int H = h;
        H %= 12;
        if (H == 0) {
            H = 12;
        }
        bool F = 1;
        if (h < 12 || (h == 12 && m == 0 && s == 0)) {
            F = 0;
        }
        printf("%s%d:%02d:%02d\n", (F ? "PM" : "AM"), H, m, s);
    }
    void tick() {
        ++s;
        if (s == 60) {
            ++m;
            s = 0;
        }
        if (m == 60) {
            ++h;
            m = 0;
        }
        if (h == 24) {
            h = 0;
        }
    }
};

int main() {
    Time t1;
    t1.printTime24();
    t1.printTime12();
    Time t2(2);
    t2.printTime24();
    t2.printTime12();
    Time t3(21, 34);
    t3.printTime24();
    t3.printTime12();
    Time t4(12, 25, 42);
    t4.printTime24();
    t4.printTime12();
    try {
        Time t5(23, 59, 99);
    } catch (invalid_argument &ex) {
        cout << ex.what() << endl;
    }
    Time t6(23, 59, 59);
    t6.tick();
    t6.printTime24();
    t6.printTime12();
    return 0;
}

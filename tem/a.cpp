#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Time {
	public :
		Time(int h = 0, int m = 0, int s = 0) {
			if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
				throw ("invalid argument!");
			}
			this->h = h;
			this->m = m;
			this->s = s;
		};
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
			if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
				throw ("invalid argument!");
			}
			this->h = h;
			this->m = m;
			this->s = s;
		}
		void operator++() {
			++this->s;
			if (this->s == 60) {
				++this->m;
				this->s = 0;
			}
			if (this->m == 60) {
				++this->h;
				this->m = 0;
			}
			if (this->h == 24) {
				this->h = 0;
			}
		}
		void operator++(int) {
			++this->s;
			if (this->s == 60) {
				++this->m;
				this->s = 0;
			}
			if (this->m == 60) {
				++this->h;
				this->m = 0;
			}
			if (this->h == 24) {
				this->h = 0;
			}
		}
		bool operator == (const Time &other) const {
			return h == other.h &&
				   m == other.m &&
				   s == other.s;
		}
		Time operator = (const Time &other) const {
			
		}
		friend ostream& operator << (ostream &output, const Time &x) {
			output << setfill('0') << setw(2) << x.h << ":" << setfill('0') << setw(2) << x.m << ":" << setfill('0') << setw(2) << x.s << "\n";
		    return output;	
		}
	private :
		int h, m, s;  
};

int main() {
    int hour, minute, second;
    cin >> hour >> minute >> second;
    try {
        Time t1(hour, minute, second);
    	Time t2;
    	cout << "t1: ";
    	cout << t1;
		cout << "t2: ";
	    cout << t2;
		t2 = t1++;
		cout << "t1: ";
		cout << t1;
		cout << "t2: ";
		cout << t2;
		if(t1 == t2)
        	cout << "t1 == t2" << endl;
    	else
            cout << "t1 != t2" << endl;
    	int s = t1;
    	cout << s << endl;
    } catch(invalid_argument &ex) {
    	cout << ex.what() << endl;	
    }
    return 0;
}

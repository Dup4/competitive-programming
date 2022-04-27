#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    int s;
    Student() {}
    Student(string name, int s) : name(name), s(s) {}
    friend istream &operator>>(istream &in, Student &x) {
        in >> x.name >> x.s;
        return in;
    }
    friend ostream &operator<<(ostream &out, const Student &x) {
        out << x.name;
        return out;
    }
    bool operator<(const Student &other) const {
        return s < other.s;
    }
};

int main() {
    int t;
    vector<Student> v;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Student st;
        v.clear();
        for (int i = 0; i < n; ++i) {
            cin >> st;
            v.push_back(st);
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); ++i) cout << v[i] << endl;
        cout << "****" << endl;
    }
    return 0;
}

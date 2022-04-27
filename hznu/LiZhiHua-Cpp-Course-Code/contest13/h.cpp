#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int id;
    Student() {}
    Student(string name, int id) : name(name), id(id) {}
    void Read() {
        cin >> name >> id;
    }
    void Print() {
        cout << id << " " << name << "\n";
    }
};

int main() {
    int t;
    cin >> t;
    Student s("Tom", 12);
    while (t--) {
        int n;
        cin >> n;
        Student st;
        for (int i = 0; i < n; ++i) {
            st.Read();
            st.Print();
        }
        cout << "****" << endl;
    }
    return 0;
}

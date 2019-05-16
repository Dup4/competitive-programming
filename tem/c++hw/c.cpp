#include <bits/stdc++.h>
using namespace std;

class Student {
	public :
		Student() {}
		Student(int num, string name, int score, char grade) {
			this->num = num;
			this->name = name;
			this->score = score;
			this->grade = grade;
		}
		int getNum() {
			return num;
		}
		string getName() {
			return name;
		}
		int getScore() {
			return score;
		}
		char getGrade() {
			return grade;
		}
		friend istream &operator >> (istream &in, Student &x) {
			in >> x.num >> x.name >> x.score;
			if (x.score >= 90) {
				x.grade = 'A';
			} else if (x.score >= 80) {
				x.grade = 'B';
			} else if (x.score >= 70) {
				x.grade = 'C';
			} else if (x.score >= 60) {
				x.grade = 'D';
			} else {
				x.grade = 'E';
			}
			return in;
		}
		friend ostream &operator << (ostream &out, const Student &x) {
			out << x.num << " " << x.name << " " << x.score << " " << x.grade << endl;
			return out;
		}
	private :
		int num;
		string name;
		int score;
		char grade;
};


int main() {
	Student x;
	ofstream out("student.txt");
	while (cin >> x) {
		if (x.getNum() == 0) {
			break;
		}
		out << x;
		//out.write(reinterpret_cast<char *>(&x), sizeof (x));
	}
	return 0;
}

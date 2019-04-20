#include <iostream>
#include <iomanip>
using namespace std;

// 输出提示信息
void preprint() {
    cout << "This program reads data and computes\n";
    cout << "body mass index and weight status.\n";
    cout << "Enter person's information:\n";
}

//输入用户信息
void input(double &height, double &weight) {
    cout << "height(in meters)? ";
    cin >> height;
    cout << "weight(in kilograms)? ";
    cin >> weight;
}

//计算BMI指数
double getBMI(double height, double weight) {
    return weight / height / height;
}

//输出BMI信息
void output(double height, double weight) {
    double BMI = getBMI(height, weight);
    cout << "Person body mass index = " << fixed << setprecision(2) << BMI << "\n";
    if (BMI < 18.5) {
        cout << "Underweight\n";
    } else if (BMI < 25.0) {
        cout << "Normal\n";
    } else if (BMI < 30.0) {
        cout << "Overweight\n";
    } else {
        cout << "Obese\n";
    }
}

int main() {
    double height, weight;
    preprint();
    input(height, weight); 
    output(height, weight);	
    return 0;
}


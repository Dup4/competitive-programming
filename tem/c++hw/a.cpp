#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    //输出提示信息
    cout << "This program reads data and computes\n";
    cout << "body mass index and weight status.\n";
    cout << "Enter person's information:\n";
	
    //输入用户信息
    double height, weight, BMI;
    cout << "height(in meters)? ";
    cin >> height;
    cout << "weight(in kilograms)? ";
    cin >> weight;

    //计算BMI指数并输出相关信息
    BMI = weight / height / height;
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
    return 0;
}

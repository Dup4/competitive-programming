#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BMI {
    public :
        //构造函数，和自定义参数列表
        BMI() {}
        BMI(string name, double height, double weight) : name(name), height(height), weight(weight) {}
        //获取用户的姓名
        string getName() {
            return name;
        }
        //获取用户的BMI指数
        double getBMI() {
            return weight / height / height; 
        }
        //获取用户的BMI指数对应的健康状态
        string reportStatus() {
            double BMI = getBMI();
            if (BMI < 18.5) {
                return "Underweight";
            } else if (BMI < 25.0) {
                return "Normal";
            } else if (BMI < 30.0) {
                return "Overweight";
            } else {
                return "Obese";
            }
        }
    private :
        //定义私有变量 用户姓名、身高、体重
        string name;
        double height, weight;
};

int main() {
    string name;
    double height, weight;
    cout << "This program reads data and computes" << endl;
    cout << "body mass index and weight status." << endl;
    cout << "Enter person's name: ";
    getline(cin, name);
    cout << "height(in meters)? ";
    cin >> height;
    cout << "weight(in kilograms)? ";
    cin >> weight;
    BMI bmi(name, height, weight);
    cout << "The BMI for " << bmi.getName() << " is " << fixed << setprecision(2) 
         << bmi.getBMI() << " " << bmi.reportStatus() << endl;
    return 0;
}

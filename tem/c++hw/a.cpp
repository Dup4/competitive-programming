#include <iostream>
#include <iomanip> 
#include <stdexcept>
using namespace std;
template <typename T>
class Vector {
public:
    Vector(int size);					// 构造函数
    Vector(int size, const T &value);         // 构造函数
    Vector(const Vector<T> &v);		// 拷贝构造函数
    virtual ~Vector();					// 析构函数
    const Vector<T> &operator=(const Vector<T> &right); // 重载赋值运算符
    T &operator[](int index);		        // 重载下标运算符
    T operator[](int index) const;		// 重载下标运算符
    int getSize() const;
    void resize(int size);
private:
    T *pVector;      // 指针，指向存放数组元素的动态分配内存空间
    int size;            // 数组长度
};
template <typename T>
Vector<T>::Vector(int size) {
    if(size > 0)
        this->size = size;
    else
        throw invalid_argument("数组长度必须是正整数!");
    pVector = new T[size];
}
template <typename T>
Vector<T>::Vector(int size, const T &value) {
    if(size > 0)
        this->size = size;
    else
        throw invalid_argument("数组长度必须是正整数!");
    pVector = new T[size];
    for(int i = 0; i < size; ++i)
        pVector[i] = value;
}
template <typename T>
Vector<T>::Vector(const Vector<T> &v) {
    size = v.size;
    pVector = new T[size];
    for(int i = 0; i < size; ++i)
        pVector[i] = v.pVector[i];
}
template <typename T>
Vector<T>::~Vector() {
    delete[] pVector;
}
template <typename T>
const Vector<T> &Vector<T>::operator=(const Vector<T> &right) {
    if(this != &right) {
        if(size != right.size) {
            delete[] pVector;
            size = right.size;
            pVector = new T[size];
        }
        for(int i = 0; i < size; ++i)
            pVector[i] = right.pVector[i];
    }
    return *this;
}
template <typename T>
T &Vector<T>::operator[](int index) {
    if(index < 0 || index > size - 1)
        throw out_of_range("数组下标超出允许范围!");
    return pVector[index];
}
template <typename T>
T Vector<T>::operator[](int index) const {
    if(index < 0 || index > size - 1)
        throw out_of_range("数组下标超出允许范围!");
    return pVector[index];
}
template <typename T>
int Vector<T>::getSize() const {
    return size;
}
template <typename T>
void Vector<T>::resize(int size) {
    if(size > 0) {
        if(this->size != size) {
            T *old = pVector;
	    pVector = new T[size];
	    int newSize = (this->size > size) ? size : this->size;
	    for(int i = 0; i < newSize; ++i)
	        pVector[i] = old[i];
		this->size = size;
		delete[] old;
	    }
	}
	else
	    throw invalid_argument("数组长度必须是正整数!");
}

template <typename T>
class Matrix {
public :
	int n, m;
	Vector < Vector <T> *> a;  
    Matrix() {}	
	Matrix(int n, int m) {
		this->n = n;
		this->m = m;
		a.resize(n);
		for (int i = 0; i < n; ++i) {
			a[i]->resize(m);
		}
	}
	Vector <T> operator [](int i) const {
		return *a[i];
	}
	Vector <T> &operator [](int i) {
		return *a[i];
	}
	Matrix operator * (const Matrix &other) const {  
		Matrix res = Matrix(n, other.m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < other.m; ++j) {
				for (int k = 0; k < m; ++k) {
					res.a[i][j] += a[i][k] * other.a[k][j];
				}
			}
		}
		return res;
	}
};
/*
template<typename T>
void printMatrix(Matrix <T> a) {
	int n = a.n, m = a.m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout.width(4);
			cout << a[i][j];  
			if (j == m - 1) {
				cout << "\n"; 
			}
		}
	}
}
*/

int main() {
    const int ROW_SIZE = 3;
    const int COLUMN_SIZE = 3;
    Matrix<int> a(ROW_SIZE, COLUMN_SIZE);
    Matrix<int> b(ROW_SIZE, COLUMN_SIZE);
    for(int i = 0; i < ROW_SIZE; ++i) {
        for(int j = 0; j < COLUMN_SIZE; ++j) {
            cin >> a[i][j];
			cout << a[i][j] << endl;
        }
    }
    for(int i = 0; i < ROW_SIZE; ++i) {
        for(int j = 0; j < COLUMN_SIZE; ++j) {
            cin >> b[i][j];
        }
    }
    //printMatrix(a * b);
    return 0;
}

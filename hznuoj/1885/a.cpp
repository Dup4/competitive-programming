#include <bits/stdc++.h>
using namespace std;

using db = double;
const int N = 110;
const db eps = 1e-8;
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
struct Matrix {
private:
	db mx[N][N];//存储矩阵数值 
	int m;//矩阵的行数
	int n;//矩阵的列数 
public:
	Matrix(int _m, int _n) { m = _m; n = _n; memset(mx, 0, sizeof(mx)); }//构造函数 
	Matrix() { m = 0; n = 0; }//默认构造函数 
	~Matrix() {}//析构函数
    db* operator[] (int x) { return mx[x]; }	
	bool is_square()const { if (m == n) return 1; else return 0; }//判断是否方阵 
	bool is_same(Matrix ma)const;//判断两个矩阵是否同型	
	bool can_mul(Matrix ma)const;//判断两个矩阵是否可以相乘	
	Matrix Gauss()const;//高斯消元法转换为行阶梯 
	bool det(db &d)const;//计算方阵行列式，返回值为是否方阵，引用参数保存结果 
	int rank()const;//计算矩阵的秩 
	Matrix transform()const;//计算转置矩阵 
	int inverse(Matrix &res)const;//计算逆矩阵，返回0表示非方阵1表示有结果2表示奇异矩阵 
								  //重载操作符 
	Matrix operator+(const Matrix &ma)const;
	Matrix operator-(const Matrix &ma)const;
	Matrix operator*(const Matrix &ma)const;
	//友元，输入输出 
	friend istream& operator >> (istream& is, Matrix &ma);
	friend ostream& operator<<(ostream& os, const Matrix &ma);
};

bool Matrix::is_same(Matrix ma)const {
	if (m == ma.m && n == ma.n)
		return 1;
	else
		return 0;
}

bool Matrix::can_mul(Matrix ma)const {
	if (n == ma.m)
		return 1;
	else
		return 0;
}

Matrix Matrix::Gauss()const {
	Matrix temp = *this;
	int Min = min(temp.m, temp.n); //min用来判断长方阵 
	db a;
	//高斯消元化为行阶梯 
	for (int k = 1; k <= Min; k++) { //k=Min时为解决m>n的情况(最后一列) 
		for (int i = k; i < temp.m; i++) {
			int flag = 0;//设置标记 
			if (sgn(fabs(temp.mx[k - 1][k - 1])) == 0) { //若主元为0
				flag = 1;//标记 
				for (int x = k; x < temp.m; x++) { //搜索开头不为0的行进行交换 
					if (sgn(fabs(temp.mx[x][k - 1])) == 0)//判0 
						continue;
					db y;
					for (int z = k - 1; z < temp.n; z++) { //搜索到开头不为0的行并交换两行 
						y = temp.mx[x][z];
						temp.mx[x][z] = temp.mx[k - 1][z];
						temp.mx[k - 1][z] = -y;//这里交换两行并添个负号，便于确定行列式符号 
					}
					flag = 0;//若交换过则主元不为0，重置标记 
					break;
				}
			}
			if (flag)//主元为0且未交换过则跳过接下来的运算 
				continue;
			//以下是高斯消元法核心 
			a = temp.mx[i][k - 1] / temp.mx[k - 1][k - 1];//计算出行首元素和主元的商 
			for (int j = k - 1; j < temp.n; j++) {
				temp.mx[i][j] -= temp.mx[k - 1][j] * a;//消元 
				if (sgn(fabs(temp.mx[i][j])) == 0) //为了输出美观 
					temp.mx[i][j] = 0;
			}
		}
	}
	return temp;
}

bool Matrix::det(db &d)const {
	if (!is_square()) return 0;
	Matrix temp = *this;
	d = 1;
	temp = temp.Gauss();//先高斯消元化为上三角 
	for (int i = 0; i < temp.m; i++) { //对角元素相乘 
		d *= temp.mx[i][i];
	}
	return 1;
}

int Matrix::rank()const {
	Matrix temp = *this;
	temp = temp.Gauss(); //高斯消元化为行阶梯 
	for (int i = 0; i < temp.m; i++) {
		int flag = 1;
		for (int j = 0; j < temp.n; j++) { //判断是否一行都为0 
			if (sgn(fabs(temp.mx[i][j])) != 0) { //如果有一个元素不为0则判断下一行 
				flag = 0;//设置标识 
				break;
			}
		}
		if (flag)//如果未设置过标识则说明元素都为0 
			return i;
	}
	return temp.m; //没有提前返回说明是行满秩 
}

Matrix Matrix::transform()const {
	Matrix temp = *this;
	temp.m = n; //交换行列长度 
	temp.n = m;
	int Max = max(n, m);
	for (int i = 0; i < Max; i++) {
		for (int j = i; j < Max; j++) { //交换行列元素(长方阵当方阵处理) 
			db a = temp.mx[i][j];
			temp.mx[i][j] = temp.mx[j][i];
			temp.mx[j][i] = a;
		}
	}
	return temp;
}

int Matrix::inverse(Matrix &res)const {
	Matrix temp = *this;
	if (!is_square()) return 0;
	db d;
	temp.det(d);
	if (sgn(fabs(d)) == 0) //行列式为0则为奇异矩阵 
		return 2;
	for (int i = 0; i < temp.n; i++) //右接单位阵 
		temp.mx[i][i + temp.n] = 1;
	temp.n *= 2; //扩大矩阵的列数，变成m*n长方阵，其中n=2*m 
	temp = temp.Gauss(); //化为行阶梯 
	for (int i = 0; i < temp.m; i++) { //左边主元化为1
		db a = temp.mx[i][i];
		for (int j = 0; j < temp.n; j++) {
			temp.mx[i][j] /= a;
		}
	}
	for (int k = 1; k < temp.m; k++) { //回代将左边化为单位阵 
		for (int i = 1; i < temp.m; i++) { //只是高斯消元倒着来而已 
			db a = temp.mx[m - k - i][m - k] / temp.mx[m - k][m - k];
			for (int j = temp.m - k; j < temp.n; j++) {
				temp.mx[temp.m - k - i][j] -= temp.mx[temp.m - k][j] * a;
			}
		}
	}
	temp.n /= 2;//矩阵大小重设为方阵 
	for (int i = 0; i < temp.n; i++) { //将右边的逆矩阵移到左边 
		for (int j = 0; j < temp.n; j++) {
			temp.mx[i][j] = temp.mx[i][j + temp.n];
		}
	}
	res = temp;
	return 1;
}

Matrix Matrix::operator+(const Matrix &ma)const {
	Matrix temp;
	assert(is_same(ma));
	temp.m = m;
	temp.n = n;
	for (int i = 0; i < ma.m; i++) {
		for (int j = 0; j < ma.n; j++) {
			temp.mx[i][j] = mx[i][j] + ma.mx[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix &ma)const {
	Matrix temp;
	assert(is_same(ma));
	temp.m = m;
	temp.n = n;
	for (int i = 0; i < ma.m; i++) {
		for (int j = 0; j < ma.n; j++) {
			temp.mx[i][j] = mx[i][j] - ma.mx[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix &ma)const {
	Matrix temp;
	assert(n == ma.m);
	temp.m = m;
	temp.n = ma.n;
	for (int i = 0; i < m; i++) { //初始化矩阵为0 
		for (int j = 0; j < ma.n; j++) {
			temp.mx[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) { //简单的矩阵乘法法则计算 
		for (int j = 0; j < ma.n; j++) {
			for (int k = 0; k < n; k++) {
				temp.mx[i][j] += mx[i][k] * ma.mx[k][j];
			}
		}
	}
	return temp;
}

istream& operator >> (istream& is, Matrix &ma) {
	for (int i = 0; i < ma.m; i++) { 
		for (int j = 0; j < ma.n; j++) {
			is >> ma.mx[i][j];
		}
	}
	return is;
}

ostream& operator<<(ostream& os, const Matrix &ma) {
	for (int i = 0; i < ma.m; i++) {
		for (int j = 0; j < ma.n; j++) {
			cout.setf(ios_base::fixed, ios_base::floatfield);
			cout.precision(2);
			os << ma.mx[i][j] << " \n"[j == ma.n - 1];
		}
	}
	return os;
}

int main() {
	int n;
	while (cin >> n) {
		if (n == 0) {
			cout << -1 << endl;
			continue;
		}
		Matrix A(n, n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> A[i][j];	
		Matrix res;
		if (A.inverse(res) == 1)
			cout << res;
		else
			cout << -1 << endl;
	}
	return 0;
}

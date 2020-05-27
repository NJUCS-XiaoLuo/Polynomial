#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polynomial
{
private:
    string name;//Polynomial's name
public:
    vector<double>Coef;//存储多项式的系数
    int length() const;//获取长度
    Polynomial();
    ~Polynomial();
    Polynomial(double* Coef,int len);//系数/长度初始化
    Polynomial(double a);//常数多项式初始化
    Polynomial(const Polynomial& Poly);//copy
    void Inputname(string& Polyname);
    string Getname();//获取多项式名称
    void nomalize();//标准化多项式

    //混合运算
    Polynomial operator+(const Polynomial& Poly);
    Polynomial operator-(const Polynomial& Poly);
    Polynomial operator*(const Polynomial& Poly);
    Polynomial operator/(const Polynomial& Poly);
    friend ostream& operator << (ostream&out, const Polynomial & Poly);
    //Polynomial integral();//不定积分
    Polynomial derivation();//求导
    Polynomial definite_integral(double a,double b);//定积分
    double value(double x);//求值函数
    
};

 #endif 
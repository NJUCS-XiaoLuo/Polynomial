#include"Polynomial.h"
using namespace std;
#define edge 1e-6

int Polynomial::length() const {
    return Coef.size();
}
Polynomial::~Polynomial(){
    Coef.clear();
}
Polynomial::Polynomial(){
    Coef.clear();
}
Polynomial::Polynomial(double* a,int len){
    Coef.clear();
    for(int i = len - 1;i >= 0;--i)
    {
        Coef.push_back(a[i]);
    }
    nomalize();
}
Polynomial::Polynomial(double a){
    Coef.clear();
    Coef.push_back(a);
}
Polynomial::Polynomial(const Polynomial& Poly){
    Coef.clear();
    string tmp_name = Poly.name;
    this->Inputname(tmp_name);
    for(int i = 0;i < Poly.length();++i)
    {
        this->Coef.push_back(Poly.Coef[i]);
    }
    nomalize();
}
void Polynomial::Inputname(string& Polyname){
    this->name = Polyname;
}
string Polynomial::Getname(){
    return this->name;
}
void Polynomial::nomalize(){
    while(Coef.size() > 1 && fabs(Coef.back()) < edge) Coef.pop_back();
    return;
}
ostream& operator << (ostream&out, const Polynomial & Poly){
    for (int i = Poly.length() - 1; i >= 0; i--) {
        //判定待输出项为0，于是不输出
        if (fabs(Poly.Coef[i]) <= edge && i != 0)continue;
        //如果输出项是最后一项
        if (fabs(Poly.Coef[i]) <= edge && i == 0 && Poly.length() == 1)cout << "0";
        //判定输出项前面的“+”“-” 号
        if (i != 0 && i != Poly.length() - 1 && Poly.Coef[i] > 0)out << '+' << " ";
        if (i != 0 && i != Poly.length() - 1 && Poly.Coef[i] < 0)out << '-' << " ";
        if (i == Poly.length() - 1 && Poly.Coef[i] < 0) out << '-';
        //针对常数项
        if (i == 0 && fabs(Poly.Coef[0]) > edge && Poly.length() > 1) 
        {
            if (Poly.Coef[0] > 0)out << '+' << " ";
            if (Poly.Coef[0] < 0)out << '-' << " ";
        }
        if(i == 0 && fabs(Poly.Coef[0]) > edge && Poly.length() == 1)
        {
            if (Poly.Coef[0] > 0)out << '+';
            if (Poly.Coef[0] < 0)out << '-';
        }
        //输出“+”-“后面的系数
        if (i != 0 && fabs(Poly.Coef[i] - 1) > edge && fabs(Poly.Coef[i] + 1) > edge)out << fabs(Poly.Coef[i]);
        if (i == 0 && fabs(Poly.Coef[0]) > edge)out << fabs(Poly.Coef[0]);
        if (i != 0 && i != 1)out << "x^" << i;
        if (i == 1) out << "x";
        out << " ";

    }
    return out;
}
Polynomial Polynomial::operator+(const Polynomial& Poly){
    Polynomial A = Polynomial(*this);
    int lenA = A.length(),lenB = Poly.length();
    int new_length = lenA >= lenB ? lenA : lenB;
    double* new_Coef = new double[new_length]();
    //for(int j = 0;j < new_length;++j) new_Coef[j] = 0;//初始化
    if(new_length == lenA){
        for(int i = 0;i < new_length;++i)
        {
            if(i < lenB)
                new_Coef[new_length - 1 - i] = A.Coef[i] + Poly.Coef[i];
            else
                new_Coef[new_length - 1 - i] = A.Coef[i];
        }
    }
    if(new_length == lenB){
        for(int i = 0;i < new_length;++i)
        {
            if(i < lenA)
                new_Coef[new_length - 1 - i] = A.Coef[i] + Poly.Coef[i];
            else
                new_Coef[new_length - 1 - i] = Poly.Coef[i];
        }
    }
    Polynomial result = Polynomial(new_Coef,new_length);
    delete []new_Coef;
    nomalize();
    return result;
}
Polynomial Polynomial::operator-(const Polynomial& Poly){
    Polynomial A = Polynomial(*this);
    int lenA = A.length(),lenB = Poly.length();
    int new_length = lenA >= lenB ? lenA : lenB;
    double* new_Coef = new double[new_length]();
    //for(int j = 0;j < new_length;++j)new_Coef[j] = 0;//初始化
    if(new_length == lenA){
        for(int i = 0;i < new_length;++i)
        {
            if(i < lenB)
                new_Coef[new_length - 1 - i] = A.Coef[i] - Poly.Coef[i];
            else
                new_Coef[new_length - 1 - i] = A.Coef[i];
        }
    }
    if(new_length == lenB){
        for(int i = 0;i < new_length;++i)
        {
            if(i < lenA)
                new_Coef[new_length - 1 - i] = A.Coef[i] - Poly.Coef[i];
            else
                new_Coef[new_length - 1 - i] = Poly.Coef[i];
        }
    }
    Polynomial result = Polynomial(new_Coef,new_length);
    delete []new_Coef;
    nomalize();
    return result;
}
Polynomial Polynomial::operator*(const Polynomial& Poly){
    Polynomial A(*this);
    Polynomial B(Poly);
    int new_length = A.length() + B.length() - 1;
    double *new_Coef = new double[new_length]();
    //for(int i = 0;i < new_length;++i) 
    //    new_Coef[i] = 0;//初始化
    //for(int t = 0;t < new_length;++t){
    //                    cout << new_Coef[new_length - t - 1] << " ";
    //                }
    for (int i = 0; i < new_length; i++) {
        for(int j = 0;j < A.length();++j){
            for(int k = 0;k < B.length();++k){
                if(j + k == i){
                    new_Coef[new_length - i - 1] += (double)A.Coef[j]*(double)B.Coef[k];                   
                    //cout << "i = " << i << ",j = " << j << ",k = " << k << endl;
                    //for(int t = 0;t < new_length;++t){
                    //   cout << new_Coef[new_length - t - 1] << " ";                   
                    //}
                     //   cout << endl;
                }
            }
        }
    }                    
                    
    Polynomial result = Polynomial(new_Coef,new_length);
    delete []new_Coef;
    return result;
}
Polynomial Polynomial::operator/(const Polynomial& Poly){
    return Polynomial(0);
}
Polynomial Polynomial::definite_integral(double a,double b){
    double *tmp = new double[length() + 1]();
    //for(int i = 0;i < length() + 1;++i)  tmp[i] = 0;
    for (int i = 0; i < length(); i++) {
        tmp[length() - i - 1] = (this->Coef[i]) / ((double)i + 1);
    }
    Polynomial integrate = Polynomial(tmp,length() + 1);
    delete []tmp;
    cout << integrate.value(b) << endl;
    cout << integrate.value(a) << endl;
    double result = integrate.value(b) - integrate.value(a); 
    return Polynomial(result);
}
double Polynomial::value(double x){
    double ans = 0;
    for (int i = length()-1; i >= 0; --i) {
        ans = ans*x+Coef[i];
    }
    return ans;
}
Polynomial Polynomial::derivation(){
    if(length() == 1)
        return Polynomial(0);
    if(length() > 1)
    {
        double* tmp = new double[length() - 1]();
        //tmp[length() - 1] = {0};
        for(int i = 1;i < length();++i)
        {
            tmp[length() - i - 1] = (this->Coef[i] * i);
        }
        Polynomial result = Polynomial(tmp,length() - 1);
        delete []tmp;
        return result;
    }
}
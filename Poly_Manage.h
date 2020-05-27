#ifndef POLY_MANAGE_H
#define POLY_MANAGE_H
#include "Polynomial.h"
#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>

using namespace std;

#define SAME_NAME -2
#define SUCCESS 1

class Polymanage
{
public:
    vector<Polynomial>Polys;
    Polymanage();
    ~Polymanage();
    int add_Poly(double* Coef, string name,int len);//向内存中添加多项式
    int getPoly(string name);//获取对应的多项式
    void out_Poly(string name);//输出多项式
    struct cal_Poly  
    {
        Polynomial MyPoly;
        int position;
        cal_Poly() {}
        cal_Poly(Polynomial poly_in, int po):MyPoly(poly_in),position(po) { }
        cal_Poly(const cal_Poly& B):MyPoly(B.MyPoly),position(B.position){}
    };
    struct cal_Operate {
        char operation;//操作符
        int position;//操作符与多项式之间的位置关系
        double a, b;//求定积分时采取的上下界
        cal_Operate(char c, int po) :operation(c), position(po) { a = b = 0; }
        cal_Operate(char c, double x, double y, int po) :operation(c), a(x), b(y), position(po) {}
    };
    stack<cal_Poly>stackPolys;//多项式栈
    stack<cal_Operate>stackOperates;//操作符栈
    int priority(char oper);
    int analyse(string expression);

    int dot;//记录小数点的位数
    double num;
    int dou;
    int de;

    void clean_up(){
        num = 0; dou = 0; de = 0; dot = 0; 
        while(!stackPolys.empty()) stackPolys.pop();
        while(!stackOperates.empty()) stackOperates.pop();
    }
    //用于判断是否要进行运算
    int do_ope_cal(char c) {//当操作符栈为空或者当前获取的操作符的优先级大于栈顶操作符的优先级时，返回0;否则返回1
        if (stackOperates.empty())return 0;//操作符栈为空
        else{//操作符栈不为空
            cal_Operate t = stackOperates.top();//获取栈顶操作符
            if (priority(c) <= priority(t.operation))return 1;//获取的运算符的优先级小于等于栈顶运算符的优先级
            else return 0;
        }
    }
    int calculate() {
        if (stackPolys.empty() || stackOperates.empty())return -1;//如果操作符栈或者多项式栈为空返回-1
        cal_Operate current_ope = stackOperates.top();//当前栈顶操作符
        stackOperates.pop();//弹出栈顶操作符，方便进行下一步的运算
        cal_Poly current_poly = stackPolys.top();//当前栈顶多项式
        stackPolys.pop();//弹出栈顶多项式，方便进行下一步的运算
        switch (current_ope.operation) {//查询当前的操作符
            case '!': {//求导运算
                if (current_ope.position <= current_poly.position)return -1;//当前操作符的位置位于当前多项式的前面（后目运算符位置错误）
                else{
                    //cout << current_poly.MyPoly.derivation() << endl;
                    stackPolys.push(cal_Poly(current_poly.MyPoly.derivation(), current_poly.position));//将运算结果重新压入多项式栈中
                    break;
                }
            }
            case '$': {
                if (current_ope.position >= current_poly.position)return -1;//当前操作符的位置位于当前多项式的后面（前目运算符位置错误）
                else{
                    double a = current_ope.a;
                    double b = current_ope.b;
                    //cout << current_poly.MyPoly.definite_integral(a, b) << endl;
                    stackPolys.push(cal_Poly(current_poly.MyPoly.definite_integral(a, b), current_poly.position));
                    break;
                }
            }
            case '*': {
                if (stackPolys.empty())return -1;
                else{
                    cal_Poly next_poly = stackPolys.top();
                    stackPolys.pop();
                    //cout << current_poly.MyPoly << endl;
                    //cout << next_poly.MyPoly << endl;
                    //cout << (current_poly.MyPoly*next_poly.MyPoly) << endl;
                    stackPolys.push(cal_Poly((current_poly.MyPoly*next_poly.MyPoly), next_poly.position));
                    break;
                }
            }
            case '+': {
                if (stackPolys.empty())return -1;
                else{
                    cal_Poly next_poly = stackPolys.top();
                    stackPolys.pop();
                    //cout << current_poly.MyPoly + next_poly.MyPoly << endl;
                    stackPolys.push(cal_Poly(current_poly.MyPoly + next_poly.MyPoly, next_poly.position));
                    break;
                }
            }
            case '-': {
                if (stackPolys.empty())return -1;
                else{
                    cal_Poly next_poly = stackPolys.top();
                    stackPolys.pop();
                    //cout << current_poly.MyPoly - next_poly.MyPoly << endl;
                    stackPolys.push(cal_Poly(current_poly.MyPoly - next_poly.MyPoly, next_poly.position));
                    break;
                }
            }
            default:break;
        }
        return 0;
    }
};

#endif 
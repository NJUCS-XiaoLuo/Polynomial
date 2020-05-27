#ifndef UI_H
#define UI_H
#include "Poly_Manage.h"
#include <string>
using namespace std;

class UI
{
public:
    UI();
    ~UI();
    //界面展示
    void UI_show();
    void menu();//主菜菜单
    void calmenu();//计算菜单
    char string_to_char(string str);//将字符串转化为字符
    bool isalpha(string str);//判断字符串是否由字母组成
    void add_polynomial();//添加多项式
    void check_polynomial();//查看表达式
    void calculate();//计算表达式
    void mix_calculate(bool &control);//混合运算
    void inverse(bool& control);//求逆运算
    void division(bool& control);//除法运算
    void root(bool& control);//求根运算
private:
    Polymanage* manage;
};

#endif

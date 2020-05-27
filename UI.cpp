#include<iostream>
#include<string>
#include "UI.h"
using namespace std;

UI::UI(){
    manage = new Polymanage();//多次显示”段错误“的原因所在，没有new
}
UI::~UI(){
    delete manage;
}

void UI::menu(){
    cout << "==============================================================" << endl;
    cout << "1.输入   2.运算   3.查看   4.退出" << endl;
    cout << "==============================================================" << endl;
    cout << "请输入你的指令:";
}
void UI::calmenu(){
    cout << "----------------------------------------" << endl;
    cout << "1.混合运算 2.求逆 3.除法 4.求根 5.退出运算" << endl;
    cout << "----------------------------------------" << endl;
    cout << "请输入需要进行的操作：";
}
void UI::UI_show(){
    cout << "\e[1;31;40m	----------------------------------------\e[0m	" << endl;
	cout << "\e[1;31;40m	|          Polynomial Calculator        |\e[0m	" << endl;
	cout << "\e[1;31;40m	----------------------------------------\e[0m	" << endl;
    menu();
    string init_str;
    bool judge = false;
    while(true)
    {
        getline(cin,init_str);
        char order = string_to_char(init_str);
        switch(order)
        {
            case '1':
                add_polynomial();
                break;
            case '2':
                calculate();
                break;
            case '3':
                check_polynomial();
                break;
            case '4':
                judge = true;
                break;
            default:
                cout << "请输入正确的指令:";
                break;
        }
        if(judge)
        {
            cout << "----------感谢您的使用----------" << endl;
            cout << "----------    ～o～   ----------" << endl;
            break;
        }
    }  
}
void UI::add_polynomial(){
    bool circle = true;//用于判断是否循环输入
    while(circle){
        cout << "请输入多项式的长度（>0):";
        int length;
        cin >> length;
        while(length < 1){
            cout << "多项式长度必须是正整数，请重新输入：";
            cin >> length;
        }
        cout << "请输入多项式的系数（从最高项开始并用空格隔开）:";
        double *Coef = new double[length]();
        //for(int i = 0;i < length;++i) Coef[i] = 0;
        for(int i = 0;i < length;++i) cin >> Coef[i];
        if(Coef[0] == 0) {
            cout << "最高项系数不能为零，请重新输入多项式系数（从最高项开始并用空格隔开）：";
            for(int i = 0;i < length;++i) cin >> Coef[i];
        }
        string name;
        cout << "请输入多项式的名称:";
        cin >> name;
        bool flag = isalpha(name);
        if(flag == false)
        {   
            while(flag == false)
            {
                cout << "多项式名称非法，请重输入新仅包含字母的多项式名称：";
                cin >> name;
                flag = isalpha(name);
            }
        }
        if(flag == true)
        {
            if(manage ->add_Poly(Coef,name,length) == SAME_NAME)
                cout << "该名称已经被使用，添加失败" << endl;
            else
            {
                cout << "添加成功！" << endl;
                delete[] Coef;
                manage->out_Poly(name);
            }
            Before:;
            cout << "是否继续添加（y/n）:";
            string order;
            cin >> order;
            if(order == "n" || order == "N") circle = false;
            else if(order == "Y" || order == "y")continue;
            else goto Before;
        }
    }
    menu();
}
void UI::calculate(){
    calmenu();
    string calorder;
    bool control = false;
    while(true)
    {
        //getline(cin,calorder);
        //char order = string_to_char(calorder);
        cin >> calorder;
        char order = calorder[0];
        switch(order)
        {
            case '1':
                mix_calculate(control);
                break;
            case '2':
                inverse(control);
                break;
            case '3':
                division(control);
                break;
            case '4':
                root(control);
                break;
            case '5':
                control = true;
                break;
            default:
                cout << "请输入正确的指令:" << endl;
                break;
        }
        if(control) break;
        calmenu();
    }  
    menu();
}
void UI::check_polynomial(){
    cout << "请输入要查询的多项式的名称:";
    string name;
    getline(cin,name);
    int check_Poly;
    check_Poly = manage->getPoly(name);
    if(check_Poly == -1)
    {
        cout << "查询的多项式不存在" << endl;
    }
    if(check_Poly >= 0)
        manage->out_Poly(name);
    menu();
}
bool UI::isalpha(string str){
    for(int j = 0;j < str.size();++j)
    {
        if(str[j] >= 'A' && str[j] <= 'Z') 
            str[j] = str[j] - 'A' + 'a';
    }
    for(int j = 0;j < str.size();++j)
    { 
        if(str[j] < 'a' || str[j] > 'z')
        {
            return false;
        }
    }
    return true;
}
char UI::string_to_char(string str){
    return str[0]; 
}
void UI::mix_calculate(bool &control){
    string expression;
Before:;
    cout << "请输入表达式：";
    cin >> expression;
    int judge = manage->analyse(expression);
    if(judge == -1){
        cout << "表达式错误！是否重新输入？(y/n):";
        B:;
        string tmp_order;
        cin >> tmp_order;
        char order = string_to_char(tmp_order);
        if(order == 'Y' || order == 'y') {
            expression.clear();
            goto Before;
        }
        else if(order == 'N' || order == 'n') return;
        else{
            cout << "是否重新输入？（y/n):";
            goto B;
        }
    }
    else{
        Polynomial result = manage->stackPolys.top().MyPoly;
        cout << "运算成功！answer = " << result << endl;
        A:;
        cout << "是否继续输入？(y/n):";
        string tmp_order;
        cin >> tmp_order;
        char order = string_to_char(tmp_order);
        if(order == 'Y' || order == 'y') {
            expression.clear();
            goto Before;
        }
        else if(order == 'N' || order == 'n') return;
        else goto A;
    }
}
void UI::inverse(bool& control){
    cout << "请输入多项式：";
    string name;
    cin >> name;
    int check_Poly;
    check_Poly = manage->getPoly(name);
    if(check_Poly == -1) 
        cout << "多项式不存在" << endl;
    if(check_Poly >= 0)
        manage->out_Poly(name);
    bool tmp = true;
    while(tmp){
        cout << "是否继续运算（y/n）:";
        string order;
        if(order == "y" || order == "Y") control = false;
        if(order == "n" || order == "N") control = true;
        else tmp = false; 
    }
}
void UI::division(bool& control){
    cout << "请输入表达式（被除式/除式）:";
    string expression;
    cin >> expression;
    string name1,name2;
    int change = 0;
    for(int i = 0;i < expression.size();++i)
    {
        if(expression[i] != '/' && change == 0)
            name1.push_back(expression[i]);
        if(expression[i] == '/') change = 1;
        if(expression[i] != '/' && change == 1)
            name2.push_back(expression[i]);
    }
    int name1_num = manage->getPoly(name1),name2_num= manage->getPoly(name2);
    if(name1_num == -1) cout << "被除式'" << name1 << "'不存在" << endl;
    if(name2_num == -1) cout << "被除式'" << name2 << "'不存在" << endl;
    if(name1_num >= 0 && name2_num >= 0){
        Polynomial quotient = manage->Polys[name1_num] / manage->Polys[name2_num];
        Polynomial remain = manage->Polys[name1_num] - quotient * manage->Polys[name2_num];
        cout << "商 = " << quotient << ",余数 = " << remain << endl;
    }
    bool tmp = true;
    while(tmp){
        cout << "是否继续运算（y/n）:";
        string order;
        if(order == "y" || order == "Y") control = false;
        if(order == "n" || order == "N") control = true;
        else tmp = false; 
    }
}
void UI::root(bool& control){
    cout << "请输入多项式：";
    string name;
    cin >> name;
    int check_Poly;
    check_Poly = manage->getPoly(name);
    if(check_Poly == -1) cout << "查询的多项式不存在" << endl;
    if(check_Poly >= 0)
        manage->out_Poly(name);
    bool tmp = true;
    while(tmp){
        cout << "是否继续运算（y/n）:";
        string order;
        if(order == "y" || order == "Y") control = false;
        if(order == "n" || order == "N") control = true;
        else tmp = false; 
    }
}
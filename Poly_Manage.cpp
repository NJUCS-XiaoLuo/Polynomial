#include "Poly_Manage.h"
#include<cmath>
#include<cctype>


Polymanage::Polymanage(){
    Polys.clear();
    dot = 0; num = 0; dou = 0; de = 0;
}
Polymanage::~Polymanage(){
    Polys.clear();
    while(!stackPolys.empty()) stackPolys.pop();
    while(!stackOperates.empty()) stackOperates.pop();
}
int Polymanage::add_Poly(double* Coef,string name,int len){
    if(Polys.size())
    {
        for(int j = 0;j < Polys.size();++j)
        {
            if(Polys[j].Getname() == name)
            {
                return SAME_NAME;
                break;
            }
        }
    }
    Polynomial new_Poly = Polynomial(Coef,len);
    new_Poly.Inputname(name);
    Polys.push_back(new_Poly);
    return SUCCESS;
}
int Polymanage::getPoly(string name){
    if(Polys.size() > 0)
    {
        for(int j = 0;j < Polys.size();++j)
        {
            if(Polys[j].Getname() == name)
                return j;
        }
    }
    return -1;
}
void Polymanage::out_Poly(string name){
    for(int j = 0;j < Polys.size();++j)
    {
        if(Polys[j].Getname() == name)
        {
            cout << name << " = " << Polys[j] << endl;
            break;
        }
    }
    return;
}
int Polymanage::priority(char oper){   
    if(oper == '(') return -1;
    if(oper == '!') return 4;
    if(oper == '$') return 3;
    if(oper == '*') return 2;
    if(oper == '+') return 1;
    if(oper == '-') return 1;
}
int Polymanage::analyse(string expression){
    string temp_poly = string();
    int index = 0;
    clean_up();
    if(expression.size() == 0) return -1;
    if(!(isalpha(expression[0]) || expression[0] == '(' || expression[0] == '$')) return -1;
    for(;index < expression.size();++index){
        char c = expression[index];
        if(c == ' ' || c == '\t') continue;
        //如果是字母
        if(isalpha(c)){
            temp_poly += c;
        }
        //如果不是字母
        if(!isalpha(c)){
            //临时存储多项式的temp_poly不为空（方便处理多项式名称多于一个字母的情况）
            if(!temp_poly.empty()){
                int i = getPoly(temp_poly);//获取该名字对应的多项式
                if(i < 0 ) return -1;//未找到该多项式（表达式中的多项式不存在）
                else{
                    Polynomial poly_put_stack = Polys[i];//找到对应的多项式
                    stackPolys.push(cal_Poly(poly_put_stack,index - 1));//将对应的多项式推入栈中
                }
                temp_poly.clear();//清空临时存储多项式的temp_poly
            }
        }
        //如果遇到定积分
        if(c == '$'){//de用来处理定积分前面的正负号,//num 用来存储计算定积分时的数字
            de = 1,dot = 0,num = 0;
            //当前运算符的优先级小于等于栈顶运算符的优先级
            if(do_ope_cal(c)){
                if(calculate() == -1) return -1;//运算错误
            }
            double a = 0,b = 0,dot = 0,num = 0;
            while(true){
                index++;
                if(expression[index] == '[') continue;
                else if(expression[index] == '-')de = -1;
                else if(expression[index] == '.')dot--; 
                else if(isdigit(expression[index])){//是数字
                    if(dot == 0) num = num * 10.0 + expression[index] - '0';//没有小数点
                    if(dot != 0) num = (double)(expression[index] - '0') * pow(10,dot);
                }
                else if(expression[index] == ','){a = num * de;num = 0;dot = 0;de = 1;}
                else if(expression[index] == ']')break;
                else return -1;
            }
            b = num * de;
            stackOperates.push(cal_Operate('$',a,b,index));           
        }
        if(c == '!'){
            if(do_ope_cal(c)){
                if(calculate() == -1) return -1;
                stackOperates.push(cal_Operate(c,index));
            }
            else stackOperates.push(cal_Operate(c,index));
        }
        if(c == '+' || c == '*' || c == '-'){
            if(do_ope_cal(c)){
                calculate();
                stackOperates.push(cal_Operate(c,index));
            }
            else stackOperates.push(cal_Operate(c,index));
        }
        if(c == '(')stackOperates.push(cal_Operate(c,index));
        if(c == ')'){
            while(stackOperates.size() > 0 && stackOperates.top().operation != '('){
                if(calculate() == -1) return -1;
            }
            if(stackOperates.size() > 0)
                stackOperates.pop();
        }
    }
    if(!temp_poly.empty()){
        int j = getPoly(temp_poly);
        if(j < 0)return -1;
        else{
            Polynomial poly_put_stack = Polys[j];
            stackPolys.push(cal_Poly(poly_put_stack,index));
        }
    }
    while (true) {
        if (stackPolys.size() == 1 && stackOperates.size() == 0) { 
            return 0; 
        }
        if (stackPolys.size() == 0) { 
            clean_up();
            return -1; 
        }
        if (stackOperates.size() == 0 && stackPolys.size() > 1) { 
            clean_up(); 
            return -1; 
        }
        if (calculate() == -1) { return -1; }
    }
    //if(calculate() == -1) return -1;
}
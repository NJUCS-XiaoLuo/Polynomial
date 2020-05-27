#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Poly
{
    string name;
    int type;
};
vector<Poly> Polys;

int main()
{
    cout << "welcome everybody" << endl;
    Polys.clear();
    cout << "please input your string and your type" << endl;
    int flag = 0;
    while(flag <= 3)
    {
        string name;
        int type;
        cout << "string:";
        cin >> name;
        cout << "type";
        cin >> type;
        Poly new_Poly;
        new_Poly.name = name;
        new_Poly.type = type;
        Polys.push_back(new_Poly);
        flag++;
    }
    for(int i = 0;i < Polys.size();++i)
    {
        cout << "(" << Polys[i].name << "," << Polys[i].type << ")" << endl;
    }
    cout << "exit..." << endl;
    return 0;
}
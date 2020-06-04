#include <iostream>
#include "DataStore.h"
using namespace std;

//一般用法，用全局变量存储,在多个类之间传递全局数据，仅用于少量配置数据的传递
DataStore DS;

int main()
{
    int i=0;
    size_t j=1;
    double k=3.14;
    std::string l="Test";

    DS.append(i);//index为0
    DS[0].SetTypeStr("int");


    DS.append(j);//index为1
    DS[1].SetTypeStr("size_t");

    DS.append(k);//index为2
    DS[2].SetTypeStr("double");

    DS.append(&l);//index为3
    DS[3].SetTypeStr("std::string *");

    DS.append(l);//index为4


    cout<<"测试数据读取，需要加强制转换才能读取"<<endl;

    cout<<"i="<<(int)DS[0]<<"\ttype:"<<DS[0].GetTypeStr()<<endl;
    cout<<"j="<<(size_t)DS[1]<<"\ttype:"<<DS[1].GetTypeStr()<<endl;
    cout<<"k="<<(double)DS[2]<<"\ttype:"<<DS[2].GetTypeStr()<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<"\ttype:"<<DS[3].GetTypeStr()<<endl;

    cout<<"l="<<DS[4].ToStdString()<<"\ttype:"<<DS[4].GetTypeStr()<<endl;

    cout<<"-----------------------------------"<<endl;

    cout<<"测试数据删除及修改"<<endl;

    DS.remove(4);//删除index为4的元素

    DS[0]=100;//修改0号位置的int元素

    cout<<"i="<<(int)DS[0]<<endl;
    cout<<"j="<<(size_t)DS[1]<<endl;
    cout<<"k="<<(double)DS[2]<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<endl;

    //由于已删除数据，下一语句无法正确执行

    // cout<<"l="<<DS[4].ToStdString()<<endl;


    cout<<"------------------------------------"<<endl;

    cout<<"测试字符下标"<<endl;
    DS.append((long double)3.14159,"PI=");

    cout<<"PI="<<(long double)DS["PI="]<<endl;

    cout<<"------------------------------------"<<endl;

    cout<<"测试利用字符下标删除"<<endl;
    DS.remove("PI=");

    //由于已删除数据
    cout<<"PI="<<(DS.exist("PI=")?(std::to_string((long double)DS["PI="])):(std::string("已删除")))<<endl;

    return 0;
}

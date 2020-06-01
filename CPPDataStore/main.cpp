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
    DS.append(j);//index为1
    DS.append(k);//index为2
    DS.append(&l);//index为3
    DS.append(l);//index为4



    cout<<"测试数据读取，需要加强制转换才能读取"<<endl;

    cout<<"i="<<(int)DS[0]<<endl;
    cout<<"j="<<(size_t)DS[1]<<endl;
    cout<<"k="<<(double)DS[2]<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<endl;

    cout<<"l="<<DS[4].ToStdString()<<endl;

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

    //由于已删除数据，下一语句无法正确执行
    //cout<<"PI="<<(long double)DS["PI="]<<endl;

    return 0;
}

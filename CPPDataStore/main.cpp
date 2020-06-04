#include <iostream>
#include "DataStore.h"
using namespace std;

//һ���÷�����ȫ�ֱ����洢,�ڶ����֮�䴫��ȫ�����ݣ������������������ݵĴ���
DataStore DS;

int main()
{
    int i=0;
    size_t j=1;
    double k=3.14;
    std::string l="Test";

    DS.append(i);//indexΪ0
    DS[0].SetTypeStr("int");


    DS.append(j);//indexΪ1
    DS[1].SetTypeStr("size_t");

    DS.append(k);//indexΪ2
    DS[2].SetTypeStr("double");

    DS.append(&l);//indexΪ3
    DS[3].SetTypeStr("std::string *");

    DS.append(l);//indexΪ4


    cout<<"�������ݶ�ȡ����Ҫ��ǿ��ת�����ܶ�ȡ"<<endl;

    cout<<"i="<<(int)DS[0]<<"\ttype:"<<DS[0].GetTypeStr()<<endl;
    cout<<"j="<<(size_t)DS[1]<<"\ttype:"<<DS[1].GetTypeStr()<<endl;
    cout<<"k="<<(double)DS[2]<<"\ttype:"<<DS[2].GetTypeStr()<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<"\ttype:"<<DS[3].GetTypeStr()<<endl;

    cout<<"l="<<DS[4].ToStdString()<<"\ttype:"<<DS[4].GetTypeStr()<<endl;

    cout<<"-----------------------------------"<<endl;

    cout<<"��������ɾ�����޸�"<<endl;

    DS.remove(4);//ɾ��indexΪ4��Ԫ��

    DS[0]=100;//�޸�0��λ�õ�intԪ��

    cout<<"i="<<(int)DS[0]<<endl;
    cout<<"j="<<(size_t)DS[1]<<endl;
    cout<<"k="<<(double)DS[2]<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<endl;

    //������ɾ�����ݣ���һ����޷���ȷִ��

    // cout<<"l="<<DS[4].ToStdString()<<endl;


    cout<<"------------------------------------"<<endl;

    cout<<"�����ַ��±�"<<endl;
    DS.append((long double)3.14159,"PI=");

    cout<<"PI="<<(long double)DS["PI="]<<endl;

    cout<<"------------------------------------"<<endl;

    cout<<"���������ַ��±�ɾ��"<<endl;
    DS.remove("PI=");

    //������ɾ������
    cout<<"PI="<<(DS.exist("PI=")?(std::to_string((long double)DS["PI="])):(std::string("��ɾ��")))<<endl;

    return 0;
}

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
    DS.append(j);//indexΪ1
    DS.append(k);//indexΪ2
    DS.append(&l);//indexΪ3
    DS.append(l);//indexΪ4



    cout<<"�������ݶ�ȡ����Ҫ��ǿ��ת�����ܶ�ȡ"<<endl;

    cout<<"i="<<(int)DS[0]<<endl;
    cout<<"j="<<(size_t)DS[1]<<endl;
    cout<<"k="<<(double)DS[2]<<endl;

    cout<<"l="<<*(std::string *)DS[3]<<endl;

    cout<<"l="<<DS[4].ToStdString()<<endl;

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

    //������ɾ�����ݣ���һ����޷���ȷִ��
    //cout<<"PI="<<(long double)DS["PI="]<<endl;

    return 0;
}

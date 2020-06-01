#ifndef DATASTORE_H
#define DATASTORE_H

//ʹ��C++14��д

#include "vector"
#include "assert.h"
#include "mutex"
#include "string"
#include "string.h"
class DataStore
{
    public:

        //�����࣬���ڴ洢����
        class Data
        {
            protected:
            void *p;
            size_t p_size;
            std::mutex mulock;

            public:

            enum
            {
                Data_Type_Default=0,
                Data_Type_StdString=1
            } Data_Type;


            //�ͷ�ָ�룬Ĭ�ϲ��������������,���ֻ��ʹ����������������
            void FreePtr()
            {
                mulock.lock();
                if(p_size!=0 && p!=NULL)
                    switch(Data_Type)
                        {
                            case Data_Type_Default:
                                delete p;
                                break;
                            case Data_Type_StdString:
                                delete (std::string *)p;
                                break;
                            default:
                                break;

                        }
                p_size=0;
                mulock.unlock();
            }
            //���캯��
            Data()
            {
              p=NULL;
              p_size=0;
              Data_Type=Data_Type_Default;
            };
            //��������
            ~Data()
            {
               FreePtr();
            }
            //���ƹ��캯��
            Data(const class Data &other)
            {
                //FreePtr();
                p=NULL;
                p_size=0;

                if(other.p_size!=0)
                {
                    mulock.lock();
                    p=new uint8_t[other.p_size];
                    p_size=other.p_size;
                    memcpy(p,other.p,p_size);
                    mulock.unlock();
                }
            }
            class Data & operator=(const class Data &other)
            {
                FreePtr();
                if(other.p_size!=0)
                {
                    mulock.lock();
                    p=new uint8_t[other.p_size];
                    p_size=other.p_size;
                    memcpy(p,other.p,p_size);
                    mulock.unlock();
                }
                return *this;
            }
            //���������͵����洢��Data�У�Ĭ�ϵĴ洢��ʽ,������Ҫ�������࣬����д����
            template <typename T> Data(const T & other)
            {
                //FreePtr();
                mulock.lock();
                p=new T;
                p_size=sizeof(T);
                *((T*)p)=other;//����
                Data_Type=Data_Type_Default;
                mulock.unlock();
            }

            template<typename T> class Data & operator=(const T & other)
            {
                FreePtr();
                mulock.lock();
                p=new T;
                p_size=sizeof(T);
                *((T*)p)=other;//����
                Data_Type=Data_Type_Default;
                mulock.unlock();
                return *this;
            }

            //Ĭ�ϵ�ת����ʽ����������Ҫ����д����
            template <typename T>  operator T()
            {
                T ret;
                mulock.lock();

                //�����������Ͳ�ͬ��ת��
                assert(p_size>=sizeof(T));

                ret=*((T*)p);
                mulock.unlock();
                return ret;
            }

            //std::string��Ĵ洢
            Data(const std::string &other)
            {
                //FreePtr();
                mulock.lock();
                p=new std::string;
                p_size=sizeof(std::string);
                *(std::string *)p=other;
                Data_Type=Data_Type_StdString;
                mulock.unlock();
            }

            class Data & operator=(const std::string &other)
            {
                FreePtr();
                mulock.lock();
                p=new std::string;
                p_size=sizeof(std::string);
                *(std::string *)p=other;
                Data_Type=Data_Type_StdString;
                mulock.unlock();
                return *this;
            };

            //��ȡ����
            std::string ToStdString()
            {
                std::string ret;
                mulock.lock();

                 //�����������Ͳ�ͬ��ת��
                assert(p_size>=sizeof(std::string));

                ret=*(std::string *)p;
                mulock.unlock();
                return ret;
            }
        };


        //���������࣬���ڴ洢��������,��Ҫ���ⲿʹ�ô���
        class DataIndex
        {
        public :
            //���캯��
            DataIndex(const std::string _indexstr)
            {
                indexstr=_indexstr;
                index=0;
            }
            DataIndex(const char * _indexstr)
            {
                indexstr=_indexstr;
                index=0;
            }
            std::string indexstr;//�����ַ���
            size_t      index;
            operator size_t()
            {
                return index;
            }
        };

        //���캯��
        DataStore()
        {

        }

        //��������
        ~DataStore()
        {
            mulock.lock();
            Array.clear();
            ArrayIndex.clear();
            mulock.unlock();
        }


        //��������
        Data & operator [](size_t i)
        {

            mulock.lock();

            //i����С��Array�Ĵ�С
            assert(i<Array.size());

            mulock.unlock();
            return Array[i];
        }

        Data &operator[](DataIndex _index)
        {
            int index=-1;
            mulock.lock();
            for(size_t i=0;i<ArrayIndex.size();i++)
            {
                if(strcmp(ArrayIndex[i].indexstr.c_str(),_index.indexstr.c_str())==0)
                {
                    index=ArrayIndex[i].index;
                    break;
                }
            }


            //index����0��Array��С֮��
            assert(index >=0);
            assert(index<(int)Array.size());
            mulock.unlock();
            return Array[index];

        }

        size_t size()
        {
            size_t ret;
            mulock.lock();
            ret=Array.size();
            mulock.unlock();
            return ret;
        }
        void append(Data data)
        {
            mulock.lock();
            Array.push_back(data);
            mulock.unlock();
        }
        bool append(Data data,DataIndex index)
        {
            bool ret=true;
            mulock.lock();
            for(size_t i=0;i<ArrayIndex.size();i++)
            {
                if(strcmp(ArrayIndex[i].indexstr.c_str(),index.indexstr.c_str())==0)
                {
                    //���������ѱ�ռ��

                    ret=false;
                    break;
                }
            }
            if(ret)
            {//������ݼ�����
                Array.push_back(data);
                index.index=Array.size()-1;
                ArrayIndex.push_back(index);
            }
            mulock.unlock();
            return ret;
        }

        //�����������ж��Ƿ����ĳ����
        bool exist(DataIndex _index)
        {
            bool ret=false;
            mulock.lock();
            for(size_t i=0;i<ArrayIndex.size();i++)
            {
                if(strcmp(ArrayIndex[i].indexstr.c_str(),_index.indexstr.c_str())==0)
                {

                    ret=true;
                    break;
                }
            }
            mulock.unlock();
            return ret;
        }

        void remove(size_t index)//ɾ������Ϊindex��ֵ
        {
            mulock.lock();

            //indexС�����ݴ�С
            assert(index<Array.size());

            Array.erase(Array.begin()+index);
            mulock.unlock();
        }
        bool remove(DataIndex _index)//ɾ������Ϊ_index��ֵ
        {
            int index=-1;
            bool ret=false;
            mulock.lock();
            for(size_t i=0;i<ArrayIndex.size();i++)
            {
                if(strcmp(ArrayIndex[i].indexstr.c_str(),_index.indexstr.c_str())==0)
                {
                    index=ArrayIndex[i].index;
                    ret=true;
                    ArrayIndex.erase(ArrayIndex.begin()+i);//ɾ������
                    break;
                }
            }


            if(ret)
            {


                //index����0��Array��С֮��
                assert(index<(int)Array.size());

                Array.erase(Array.begin()+index);
            }
            mulock.unlock();
            return ret;
        }


    protected:

    private:
        std::mutex mulock;
        std::vector<Data>   Array;
        std::vector<DataIndex> ArrayIndex;
};

#endif // DATASTORE_H

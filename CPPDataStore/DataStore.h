#ifndef DATASTORE_H
#define DATASTORE_H

//使用C++14编写

#include "vector"
#include "assert.h"
#include "mutex"
#include "string"
#include "string.h"
class DataStore
{
    public:

        //数据类，用于存储数据
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


            //释放指针，默认不会调用析构函数,因此只能使用无需析构的类型
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
            //构造函数
            Data()
            {
              p=NULL;
              p_size=0;
              Data_Type=Data_Type_Default;
            };
            //析构函数
            ~Data()
            {
               FreePtr();
            }
            //复制构造函数
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
            //将其它类型的数存储在Data中，默认的存储方式,如是需要析构的类，单独写函数
            template <typename T> Data(const T & other)
            {
                //FreePtr();
                mulock.lock();
                p=new T;
                p_size=sizeof(T);
                *((T*)p)=other;//复制
                Data_Type=Data_Type_Default;
                mulock.unlock();
            }

            template<typename T> class Data & operator=(const T & other)
            {
                FreePtr();
                mulock.lock();
                p=new T;
                p_size=sizeof(T);
                *((T*)p)=other;//复制
                Data_Type=Data_Type_Default;
                mulock.unlock();
                return *this;
            }

            //默认的转换方式，特殊类需要单独写函数
            template <typename T>  operator T()
            {
                T ret;
                mulock.lock();

                //不允许部分类型不同的转换
                assert(p_size>=sizeof(T));

                ret=*((T*)p);
                mulock.unlock();
                return ret;
            }

            //std::string类的存储
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

            //读取函数
            std::string ToStdString()
            {
                std::string ret;
                mulock.lock();

                 //不允许部分类型不同的转换
                assert(p_size>=sizeof(std::string));

                ret=*(std::string *)p;
                mulock.unlock();
                return ret;
            }
        };


        //数据引索类，用于存储数据引索,不要在外部使用此类
        class DataIndex
        {
        public :
            //构造函数
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
            std::string indexstr;//引索字符串
            size_t      index;
            operator size_t()
            {
                return index;
            }
        };

        //构造函数
        DataStore()
        {

        }

        //析构函数
        ~DataStore()
        {
            mulock.lock();
            Array.clear();
            ArrayIndex.clear();
            mulock.unlock();
        }


        //访问数据
        Data & operator [](size_t i)
        {

            mulock.lock();

            //i必须小于Array的大小
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


            //index需在0与Array大小之间
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
                    //引索名称已被占用

                    ret=false;
                    break;
                }
            }
            if(ret)
            {//添加数据及引索
                Array.push_back(data);
                index.index=Array.size()-1;
                ArrayIndex.push_back(index);
            }
            mulock.unlock();
            return ret;
        }

        //从数据引索判断是否存在某数据
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

        void remove(size_t index)//删除引索为index的值
        {
            mulock.lock();

            //index小于数据大小
            assert(index<Array.size());

            Array.erase(Array.begin()+index);
            mulock.unlock();
        }
        bool remove(DataIndex _index)//删除引索为_index的值
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
                    ArrayIndex.erase(ArrayIndex.begin()+i);//删除引索
                    break;
                }
            }


            if(ret)
            {


                //index需在0与Array大小之间
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

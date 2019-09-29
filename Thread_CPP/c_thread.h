#ifndef __C_THREAD_H__
#define __C_THREAD_H__
#include "pthread.h"
#include "vector"

class C_Thread
{
    public:
    typedef void *(*thread_fun_t)(void *);
    typedef struct _thread_t
    {
        void * class_pointer; //指向类的指针
        pthread_t thread_tid; //pthread数据
        thread_fun_t callback;//回调数据
        void * arg;//参数
        bool  Is_Running;//是否在运行
        void * ret;//返回值
    } thread_t;

        C_Thread();
        virtual ~C_Thread();
    virtual void     * thread_run(void *);//线程运行函数，主要用于在子类中重载

    //信息获取函数
    virtual std::vector<thread_t *>   Get_Thread_Vector();//获得已创建的线程的向量
    virtual size_t                    Get_Number_Of_Thread();//获取线程数量（包括已经停止的）
    virtual size_t                    Get_Number_Of_ActiveThread();//获取正在运行的线程
    virtual size_t                    Clear_Thread_Vector();//删除未运行的线程数据，除非线程数据实在太多，否则最好不要清理



    //线程相关函数（主要是封装pthread库）
    virtual thread_t * thread_struct_new();//创建结构体
    virtual void       thread_struct_delete(thread_t *);//结构体删除
    virtual int        thread_cancel(thread_t *);//线程取消
    virtual int        thread_join(thread_t *);//等待线程
    virtual int        thread_create();//创建线程
    virtual int        thread_create(void *);//创建线程，参数为线程函数需要的参数
    virtual int        thread_create(thread_fun_t fun,void *arg=NULL);//创建线程，参数分别是线程函数及参数

    protected:
    std::vector<thread_t *> Thread_Vector;//线程结构体指针向量


    private:
    static void *thread_process(void *);//真正的线程处理函数
};

#endif // __C_THREAD_H__

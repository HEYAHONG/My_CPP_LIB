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
        void * class_pointer; //ָ�����ָ��
        pthread_t thread_tid; //pthread����
        thread_fun_t callback;//�ص�����
        void * arg;//����
        bool  Is_Running;//�Ƿ�������
        void * ret;//����ֵ
    } thread_t;

        C_Thread();
        virtual ~C_Thread();
    virtual void     * thread_run(void *);//�߳����к�������Ҫ����������������

    //��Ϣ��ȡ����
    virtual std::vector<thread_t *>   Get_Thread_Vector();//����Ѵ������̵߳�����
    virtual size_t                    Get_Number_Of_Thread();//��ȡ�߳������������Ѿ�ֹͣ�ģ�
    virtual size_t                    Get_Number_Of_ActiveThread();//��ȡ�������е��߳�
    virtual size_t                    Clear_Thread_Vector();//ɾ��δ���е��߳����ݣ������߳�����ʵ��̫�࣬������ò�Ҫ����



    //�߳���غ�������Ҫ�Ƿ�װpthread�⣩
    virtual thread_t * thread_struct_new();//�����ṹ��
    virtual void       thread_struct_delete(thread_t *);//�ṹ��ɾ��
    virtual int        thread_cancel(thread_t *);//�߳�ȡ��
    virtual int        thread_join(thread_t *);//�ȴ��߳�
    virtual int        thread_create();//�����߳�
    virtual int        thread_create(void *);//�����̣߳�����Ϊ�̺߳�����Ҫ�Ĳ���
    virtual int        thread_create(thread_fun_t fun,void *arg=NULL);//�����̣߳������ֱ����̺߳���������

    protected:
    std::vector<thread_t *> Thread_Vector;//�߳̽ṹ��ָ������


    private:
    static void *thread_process(void *);//�������̴߳�����
};

#endif // __C_THREAD_H__

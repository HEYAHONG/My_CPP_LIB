#include "c_thread.h"

C_Thread::C_Thread()
{
    //ctor
    Thread_Vector.clear();

}

void * C_Thread::thread_run(void * argv)
{
    //É¶Ò²²»×ö
    return NULL;
}
std::vector<C_Thread::thread_t *> C_Thread::Get_Thread_Vector()
{
    return Thread_Vector;
}

size_t                            C_Thread::Get_Number_Of_Thread()
{
    return Thread_Vector.size();
}

size_t                            C_Thread::Get_Number_Of_ActiveThread()
{
    size_t i=0,ret=0;
    for(i=0;i<Thread_Vector.size();i++)
    {
        if(Thread_Vector[i]->Is_Running)
            ret++;
    }
    return ret;
}
size_t                            C_Thread::Clear_Thread_Vector()
{
    size_t i=0,ret=0;
    for(i=0;i<Thread_Vector.size();i++)
    {
        if(Thread_Vector[i]->Is_Running)
        {
            pthread_cancel(Thread_Vector[i]->thread_tid);
            thread_struct_delete(Thread_Vector[i]);
            ret++;
            //Thread_Vector[i]=NULL;
            Thread_Vector.erase(Thread_Vector.begin()+i);
        }
    }
    return ret;
}

C_Thread::thread_t * C_Thread::thread_struct_new()
{
    thread_t *p=new thread_t;
    p->callback=NULL;
    p->class_pointer=this;
    p->arg=NULL;
    p->thread_tid=0;
    p->Is_Running=false;
    return p;
}
void C_Thread::thread_struct_delete(thread_t *p)
{
    if(p!=NULL)
        delete p;
}
int C_Thread::thread_cancel(thread_t * p)
{
    if(p->Is_Running)
        return pthread_cancel(p->thread_tid);
    return 0;
}
int C_Thread::thread_join(thread_t * p)
{
    if(p->Is_Running)
        return pthread_join(p->thread_tid,&(p->ret));
    return 0;
}
int C_Thread::thread_create()
{
    thread_t * p=thread_struct_new();
    int ret=pthread_create(&p->thread_tid,NULL,thread_process,p);
    if(ret)
        {
        thread_struct_delete(p);
        return ret;
        }
    Thread_Vector.push_back(p);
    return 0;
}
int C_Thread::thread_create(void *arg)
{
   thread_t * p=thread_struct_new();
    p->arg=arg;
    int ret=pthread_create(&p->thread_tid,NULL,thread_process,p);
    if(ret)
        {
        thread_struct_delete(p);
        return ret;
        }
    Thread_Vector.push_back(p);
    return 0;
}
int C_Thread::thread_create(C_Thread::thread_fun_t fun,void *arg)
{
    thread_t * p=thread_struct_new();
    p->callback=fun;
    p->arg=arg;
    int ret=pthread_create(&p->thread_tid,NULL,thread_process,p);
    if(ret)
        {
        thread_struct_delete(p);
        return ret;
        }
    Thread_Vector.push_back(p);
    return 0;
}
void * C_Thread::thread_process(void *argv)
{
    thread_t * p=(thread_t*)argv;
    void * ret=NULL;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    p->Is_Running=true;
    if(p->callback !=NULL)
        ret=p->callback(p->arg);
    else
        ret=((C_Thread *)p->class_pointer)->thread_run(p->arg);
    p->Is_Running=false;
    p->ret=ret;
    return ret;
}

C_Thread::~C_Thread()
{
    //dtor
    size_t i=0;
    for(i=0;i<Thread_Vector.size();i++)
    {
        if(Thread_Vector[i]->Is_Running)
        {
        pthread_cancel(Thread_Vector[i]->thread_tid);
        }
        thread_struct_delete(Thread_Vector[i]);
    }
    Thread_Vector.clear();
}

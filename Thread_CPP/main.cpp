#include "c_thread.h"
#include "stdio.h"
class test:public C_Thread
{
    public:
    test()
    {
        thread_create();
    }
    void *thread_run(void *)
    {
        while(1)
        {

            printf("test\n");
            break;//getchar();
        }
        return NULL;
    }
};
void * test_fun(void *)
{
    while(1)
    {
        printf("test fun\n");
        break;//getchar();
    }
    return NULL;
}

void *test_fun2(void * p)
{
    while(1)
    {
        printf((char *)p);
        break;//getchar();
    }
    return NULL;
}
int main(int argc,char *argv[])
{
    test temp;
    temp.thread_create(test_fun);
    temp.thread_create(test_fun2,(void *)"test fun2\n");
    printf("main thread:%d\n",temp.Get_Number_Of_Thread());
    while(1)
    {

        if(temp.Get_Number_Of_ActiveThread())
        {
            printf("%d",temp.Get_Number_Of_ActiveThread());
        }
        else
            getchar();
    }
    return 0;
}

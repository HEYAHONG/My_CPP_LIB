#include "modbus_tcp.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
int __cdecl Debug_Printf_NULL(FILE * fp,const char * format,...)
{
    return 0; //啥也不做
}
#ifdef __cplusplus
}
#endif // __cplusplus

Modbus_TCP::Modbus_TCP()
{
    //ctor
    SetDebug(false,false);
    bind_ip="127.0.0.1";
    bind_port=1502;
    ctx=NULL;
    mb_mapping=NULL;
    s=-1;
    callback_Arry.clear();
   // init();
}

Modbus_TCP::Modbus_TCP(std::string ip,int16_t port)
{
    SetDebug(false,false);
    bind_ip=ip;
    bind_port=port;
    ctx=NULL;
    mb_mapping=NULL;
    s=-1;
    callback_Arry.clear();
   // init();
}

void Modbus_TCP::SetIP(std::string ip,int16_t port)
{
    bind_ip=ip;
    bind_port=port;
}

void Modbus_TCP::SetDebug(bool Is_Debug_Error,bool Is_Debug_Info)
{
    setbuf(stdout,NULL);
    setbuf(stderr,NULL);
    if(Is_Debug_Error)
        Debug_Error=fprintf;
    else
        Debug_Error=Debug_Printf_NULL;
    if(Is_Debug_Info)
        Debug_Info=fprintf;
    else
        Debug_Info=Debug_Printf_NULL;
}

bool Modbus_TCP::Get_Is_Debug_Error()
{
    if(Debug_Error==Debug_Printf_NULL)
        return false;
    else
        return true;
}

bool Modbus_TCP::Get_IS_Debug_Info()
{
    if(Debug_Info==Debug_Printf_NULL)
        return false;
    else
        return true;
}

void Modbus_TCP::init()
{
    Debug_Info(stdout,"Modbus TCP： Init!\n");
    if((ctx = modbus_new_tcp(bind_ip.c_str(), bind_port)) == NULL)
    {
        Debug_Error(stderr,"Can not new modbus_Tcp:%s\n",modbus_strerror(errno));
        return;
    }
    //点数尽可能大。
    mb_mapping = modbus_mapping_new(65535, 65535, 65535, 65535);
    if (mb_mapping == NULL) {
        Debug_Error(stderr,"Modbus TCP： Failed to allocate the mapping: %s\n",modbus_strerror(errno));
        modbus_free(ctx);
        return;
    }

}
void Modbus_TCP::start()
{
    Debug_Info(stdout,"Modbus TCP： Start!\n");
    if(ctx == NULL || mb_mapping == NULL)
    {
        Debug_Error(stderr,"Modbus TCP： Not init!\n");
        return;
    }

    s = modbus_tcp_listen(ctx, 1);

    if((s!=-1)&& (ctx!=NULL))
    {
    int pret=pthread_create(&Server_thread, NULL,Server_thread_loop,this);
    if(pret)
        {
            Debug_Error(stderr,"Modbus TCP： Can't Create Thread\n");
            close(s);
            s=-1;
            return;
        }
    Debug_Info(stdout,"\nModbus Server Started!(%s:%d)\n",bind_ip.c_str(),bind_port);
    }
    else
    {
    Debug_Error(stdout,"\nModbus TCP： Can't Listen %s:%d\n",bind_ip.c_str(),bind_port);
    return;//退出程序
    }

}

void * Modbus_TCP::Server_thread_loop(void * argv)
{
Modbus_TCP * p=(Modbus_TCP *)argv;
pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
while(1)
    {
        modbus_tcp_accept(p->ctx, &(p->s));
        p->Debug_Info(stdout,"Modbus TCP：Connected!\n");
        for (;;)
        {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc;

            rc = modbus_receive(p->ctx, query);
            if (rc > 0)
            {
                //输出查询的帧
                p->Debug_Info(stdout,"Modbus TCP：The Request function Code:0x%02X,Data_length=%d,Data:\n",query[7],query[5]);
                int temp=0;
                for(temp=0;temp<query[5];temp++)
                    {
                        p->Debug_Info(stdout,"%02X",query[6+temp]);
                    }
                p->Debug_Info(stdout,"\n");


                //处理回调函数需要的变量
                uint8_t Modbus_request[MODBUS_TCP_MAX_ADU_LENGTH];
                int Modbus_request_length;
                //运行回调函数
                {
                Modbus_request_length=query[5];
                memcpy(Modbus_request,&query[6],Modbus_request_length);
                size_t i=0;
                for(i=0;i<((p->callback_Arry).size());i++)
                    (p->callback_Arry[i])(Modbus_request,Modbus_request_length,p->mb_mapping);
                }

                Modbus_request_length=query[5];
                memcpy(Modbus_request,&query[6],Modbus_request_length);

                /* rc is the query size */
                modbus_reply(p->ctx, query, rc, p->mb_mapping);

            }
            else if (rc == -1)
                {
                /* Connection closed by the client or error */
                break;
                }
        }
        p->Debug_Info(stdout,"\nModbus TCP：Closed\n");

    }

}

void Modbus_TCP::stop()
{
Debug_Info(stdout,"Modbus TCP：Stop!\n");
if(s==-1)
{
    Debug_Error(stderr,"Modbus TCP：Not Start!\n");
}
int pret=pthread_cancel(Server_thread);
if(pret)
    {
        Debug_Error(stderr,"\nModbus TCP：Can't Cancel Thread\n");
        return;
    }

close(s);
s=-1;

}

void Modbus_TCP::server_callback_register(modbus_callback fun)
{
    callback_Arry.push_back(fun);
}

void Modbus_TCP::server_callback_unregister(modbus_callback fun)
{
size_t i=0;
for(i=0;i<(callback_Arry.size());i++)
{
    if(callback_Arry[i]==fun)
    {
        callback_Arry[i]=callback_Arry[callback_Arry.size()-1];
        callback_Arry.pop_back();
        break;
    }
}
}
Modbus_TCP::~Modbus_TCP()
{
    //dtor
    pthread_cancel(Server_thread);
    if(mb_mapping!=NULL)
        modbus_mapping_free(mb_mapping);
    if(ctx!= NULL)
    {
        modbus_close(ctx);
        modbus_free(ctx);
    }
    callback_Arry.clear();
}

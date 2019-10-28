#include "modbus_server.h"

//��������
int s = -1;
modbus_t *ctx=NULL;
modbus_mapping_t *mb_mapping=NULL;
pthread_t modbus_server_loop_thread;

//����ص�������Ҫ�ı���
uint8_t Modbus_request[MODBUS_TCP_MAX_ADU_LENGTH];
int Modbus_request_length;
modbus_callback_t modbus_callback_start={NULL,NULL};


//modbus����ѭ����
void * modbus_server_loop(void * argv)
{
pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
while(1)
    {
        modbus_tcp_accept(ctx, &s);
        printf("\nConnected!\n");
        for (;;)
        {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc;

            rc = modbus_receive(ctx, query);
            if (rc > 0)
            {
                //�����ѯ��֡
//                printf("The Request function Code:0x%02X,Data_length=%d,Data:\n",query[7],query[5]);
//                int temp=0;
//                for(temp=0;temp<query[5];temp++)
//                    {
//                        printf("%02X",query[6+temp]);
//                    }
//                printf("\n");

                {//ִ�лص�����
                Modbus_request_length=query[5];
                memcpy(Modbus_request,&query[6],Modbus_request_length);
                if(modbus_callback_start.modbus_callback_fun !=NULL)
                    {
                        (modbus_callback_start.modbus_callback_fun)(Modbus_request,Modbus_request_length,mb_mapping);
                        if(modbus_callback_start.next != NULL)
                            {
                            modbus_callback_t * next=modbus_callback_start.next;
                            while(next !=NULL)
                                {
                                    (next->modbus_callback_fun)(Modbus_request,Modbus_request_length,mb_mapping);
                                    next=next->next;
                                }
                            }

                    }
                }

                /* rc is the query size */
                modbus_reply(ctx, query, rc, mb_mapping);

            }
            else if (rc == -1)
                {
                /* Connection closed by the client or error */
                break;
                }
        }
        printf("\nClosed\n");

    }
}

void modbus_server_start(string ip,uint16_t port)
{

    ctx = modbus_new_tcp(ip.c_str(), port);



    //���������ܴ�
    mb_mapping = modbus_mapping_new(65536, 65536, 65536, 65536);
    if (mb_mapping == NULL) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        modbus_free(ctx);
        exit(-1);
    }

//    {//��������
//    mb_mapping->tab_registers[0]=0xff00;
//    mb_mapping->tab_registers[1]=0x00ff;
//    mb_mapping->tab_bits[0]=0x81;
//    mb_mapping->tab_bits[1]=0x00;
//    }

    s = modbus_tcp_listen(ctx, 1);

    if((s!=-1)&& (ctx!=NULL))
    {
    int pret=pthread_create(&modbus_server_loop_thread, NULL, modbus_server_loop,NULL);
    if(pret)
        {
            printf("\nCan't Create Thread\n");
            exit(0);
        }
    printf("\nModbus Server Started!(%s:%d)\n",ip.c_str(),port);
    }
    else
    {
    printf("\nCan't Listen %s:%d\n",ip.c_str(),port);
    exit(0);//�˳�����
    }
}

void modbus_server_stop()
{
int pret=pthread_cancel(modbus_server_loop_thread);
if(pret)
    {
        printf("\nCan't Cancel Thread\n");
        exit(0);
    }
if (s != -1)
    {
        close(s);
    }
modbus_mapping_free(mb_mapping);
modbus_close(ctx);
modbus_free(ctx);
printf("\nModbus Server Exited!\n");
ctx=NULL;
}

//ע��ص�����
void modbus_server_callback_register(modbus_callback modbus_callback_fun)
{
if(modbus_callback_fun == NULL) return; //������

if(modbus_callback_start.modbus_callback_fun == NULL)
    {
    modbus_callback_start.modbus_callback_fun=modbus_callback_fun;
    modbus_callback_start.next=NULL;
    }
else
    {
    modbus_callback_t * next=modbus_callback_start.next;
    if(next != NULL)
        {
            while(next->next != NULL)
            {
            next=next->next;
            }
            next->next=(modbus_callback_t*)malloc(sizeof(modbus_callback_t));
            next->next->modbus_callback_fun=modbus_callback_fun;
            next->next->next=NULL;
        }
    else
        {
        modbus_callback_start.next=(modbus_callback_t*)malloc(sizeof(modbus_callback_t));
        modbus_callback_start.next->modbus_callback_fun=modbus_callback_fun;
        modbus_callback_start.next->next=NULL;
        }

    }
}

//ȡ��ע��ص�����
void modbus_server_callback_unregister(modbus_callback modbus_callback_fun)
{
if(modbus_callback_fun == NULL) return; //������

if(modbus_callback_start.modbus_callback_fun != NULL)
    {
        if(modbus_callback_start.modbus_callback_fun == modbus_callback_fun)
            {
                if(modbus_callback_start.next != NULL)
                    {
                    modbus_callback_t * next=modbus_callback_start.next;
                    modbus_callback_start.modbus_callback_fun=modbus_callback_start.next->modbus_callback_fun;
                    modbus_callback_start.next=modbus_callback_start.next->next;
                    free(next);
                    }
                else
                    modbus_callback_start.modbus_callback_fun=NULL;
            }
        else if(modbus_callback_start.next != NULL)
            {
            modbus_callback_t * Before=NULL,* Current=NULL,* Next=NULL;
            Before  =   &modbus_callback_start;
            Current =   modbus_callback_start.next;
            Next    =   modbus_callback_start.next->next;
            do
            {
             if(Current->modbus_callback_fun == modbus_callback_fun)
             {
             Before->next=Next;
             free(Current);
             break;
             }
             if(Next != NULL)
             {
             Before=Current;
             Current=Next;
             Next=Next->next;
             }

            }
            while(Next != NULL);
            }

    }
}

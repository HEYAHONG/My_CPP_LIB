#include "stdio.h"
#include "c_socket.h"

class test_server:public C_Socket
{
    public:
    void socket_server_OnReceiveData(Addr *p,void *buff,size_t count)
    {
        size_t i=0;

        for(i=0;i<count;i++)
        {
            printf("%c",((char *)buff)[i]);
        }
        C_Socket::socket_server_OnReceiveData(p,buff,count);
    }
};

class test_client:public C_Socket
{
    public:
        Addr * client=NULL;
        void socket_client_OnConnected(Addr *p)
        {
            client=p;
            printf("Server Connected£¡\n");
            return;
        }

};
int main(int argc,char *argv[])
{
    printf("main started!\n");
    printf("Server(S)/Client(C),Please Input a Char:");
    char c=0;
    scanf("%c",&c);
    if(c=='S' || c=='s')
    {
    printf("Start Server!\n");
    test_server temp;
    temp.socket_server("0.0.0.0",5000);
    }
    if(c=='C' || c== 'c')
    {
    printf("Start Client!\n");
    test_client temp;
    char buff[4096];
    temp.socket_client("127.0.0.1",5000);
    while(1)
    {
        if(temp.client !=NULL)
        {
            scanf("%s",buff);
            temp.socket_write(temp.client,buff,strlen(buff));
        }
    }
    }
    printf("input error!\n");

}

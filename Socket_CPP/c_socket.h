#ifndef C_SOCKET_H
#define C_SOCKET_H
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "errno.h"
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <signal.h>
#include <sys/types.h>
#ifdef WIN32
#include <WS2tcpip.h>
#include <winsock2.h>
#ifndef WINVER
#define WINVER 0x0501
# endif
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif // WIN32

class C_Socket
{
    public:
    static int is_socket_init;
    static int class_count;
//    #ifdef WIN32
//    static WORD wVersionRequested;
//    static WSADATA wsaData;
//    #endif // WIN32
    //用到的地址定义
    class Addr
        {
        public:
            enum Addr_type
            {
            Addr_Uninitiated=0,
            Addr_fd_Initiated,
            Addr_ad_Initiated,
            Addr_Server,
            Addr_Client,
            Addr_To_Server
            };
            typedef struct sockaddr_in sockaddr_in_t;
            typedef struct sockaddr_in6 sockaddr_in_t6;
            int fd;//文件标识
            int tp;//地址状态
            sockaddr_in_t *sockaddr;
            sockaddr_in_t6 *sockaddr6;
            size_t         sockaddr_size;
            bool Is_IPV6;
            Addr(bool is_ipv6=false)
            {
                Is_IPV6=is_ipv6;
                if(!is_ipv6)
                {
                    sockaddr=new sockaddr_in_t;
                    sockaddr_size=sizeof(sockaddr_in_t);
                    memset(sockaddr,0,sockaddr_size);
                    tp=Addr_Uninitiated;
                    sockaddr6=NULL;
                }
                else
                {
                    sockaddr6=new sockaddr_in_t6;
                    sockaddr_size=sizeof(sockaddr_in_t6);
                    memset(sockaddr6,0,sockaddr_size);
                    tp=Addr_Uninitiated;
                    sockaddr=NULL;
                }
            }
            ~Addr()
            {
                if(sockaddr!=NULL)
                    delete sockaddr;
                if(sockaddr6!=NULL)
                    delete sockaddr6;
            }


        };
        C_Socket();
        virtual ~C_Socket();

        unsigned long ip_default;
        unsigned short port_default;

        //设定是否为ipv6，一般在构造函数中调用
        bool Is_IPV6;
        virtual void set_Is_IPV6(bool is_ipv6)
        {
            Is_IPV6=is_ipv6;
        }
        virtual bool get_Is_IPV6()
        {
            return Is_IPV6;
        }

        //封装socket函数
        virtual Addr * socket_new(int type=SOCK_STREAM,int protocol=0);
        virtual void   socket_delete(Addr *p);
//        virtual void   socket_setaddr(Addr *p,unsigned long addr=INADDR_ANY,unsigned short port=5000);
        virtual void   socket_setaddr(Addr *p,const char * addr,unsigned short port=5000);
        virtual int    socket_bind(Addr *p);
        virtual int    socket_listen(Addr *p,int backlog=2);
        virtual Addr * socket_accept(Addr *p);
        virtual int    socket_connect(Addr*p);
        virtual int    socket_read(Addr *p,void *buff,size_t count);
        virtual int    socket_write(Addr *p,void *buff,size_t count);

        //服务器自定义函数
        enum Server_Error
        {
            Server_Socket_Error=1,
            Server_Bind_Error,
            Server_Listen_Error,
            Server_Accept_Error,
            Server_Read_Error

        };
        virtual void   socket_server(const char * ip_addr=NULL,unsigned short ip_port=5000,int listen_backlog=2,int socket_type=SOCK_STREAM,int socket_protocol=0);
        virtual void   socket_server_OnAccept(Addr *p);
        virtual void   socket_server_OnError(int Server_Error);
        virtual void   socket_server_OnReceiveData(Addr *p,void * buff,size_t count);

        //客户端自定义函数
        enum Client_Error
        {
            Client_Socket_Error=1,
            Client_Connect_Error
        };
        virtual void   socket_client(const char * ip_addr,unsigned short ip_port=5000,int socket_type=SOCK_STREAM,int socket_protocol=0);
        virtual void   socket_client_OnConnected(Addr *p);
        virtual void   socket_client_OnError(int Client_Error);



    protected:

    private:

};

#endif // C_SOCKET_H

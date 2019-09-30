#include "c_socket.h"
int C_Socket::is_socket_init=0;
int C_Socket::class_count=0;
#ifdef WIN32
static WSADATA wsaData;
static WORD wVersionRequested;
#endif // WIN32
C_Socket::C_Socket()
{
    if(is_socket_init <= 0)
    {
        #ifdef WIN32
        wVersionRequested = MAKEWORD( 1, 1 );
        if(0==WSAStartup( wVersionRequested, &wsaData ))
            C_Socket::is_socket_init++;
        #endif // WIN32
    }
    class_count++;
    //ctor
}

C_Socket::Addr * C_Socket::socket_new(int type,int protocal)
{
    Addr * p=new Addr;
    p->fd=socket(AF_INET,type,protocal);
    if(p->fd < 0)
    {
        delete p;
        return NULL;
    }
    else
    {
        p->tp=Addr::Addr_fd_Initiated;
        return p;
    }
}
void C_Socket::socket_delete(C_Socket::Addr * p)
{
    if(p!=NULL)
    {
        if(p->tp != Addr::Addr_Uninitiated)
            close(p->fd);
        delete p;
    }
}
void C_Socket::socket_setaddr(C_Socket::Addr *p,unsigned long addr,unsigned short port)
{
    if(p!=NULL)
    {
        p->sockaddr->sin_family=AF_INET;
        p->sockaddr->sin_addr.s_addr=htonl(addr);
        p->sockaddr->sin_port=htons(port);
        p->tp=Addr::Addr_ad_Initiated;
    }
}
void C_Socket::socket_setaddr(C_Socket::Addr *p,const char *addr,unsigned short port)
{
    if(p!=NULL)
    {
        p->sockaddr->sin_family=AF_INET;
        p->sockaddr->sin_port=htons(port);
        p->sockaddr->sin_addr.s_addr=inet_addr(addr);
        p->tp=Addr::Addr_ad_Initiated;

    }
}
int C_Socket::socket_bind(C_Socket::Addr *p)
{
    int ret;
    if(p == NULL)
        return -1;
    ret=bind(p->fd,(struct sockaddr*)p->sockaddr,sizeof(struct sockaddr));
    //printf("%d:%s",errno,strerror(errno));
    if(ret == 0)
    {
        p->tp=Addr::Addr_Server;
    }
    return ret;
}
int C_Socket::socket_listen(C_Socket::Addr *p,int backlog)
{
    int ret;
    if(p == NULL)
        return -1;
    ret=listen(p->fd,backlog);
    return ret;
}

C_Socket::Addr * C_Socket::socket_accept(C_Socket::Addr *p)
{
    if(p==NULL)
        return NULL;
    if(p->tp != Addr::Addr_Server)
        return NULL;
    Addr * client=new Addr;
    int ret=sizeof(struct sockaddr);
    memcpy(client->sockaddr,p->sockaddr,p->sockaddr_size);
    client->fd=accept(p->fd,(struct sockaddr *)client->sockaddr,&ret);
    if(client->fd < 0)
    {
        delete client;
        return NULL;
    }
    else
    {
        client->tp=Addr::Addr_Client;
        client->sockaddr_size=ret;
        return client;
    }
}
int  C_Socket::socket_connect(C_Socket::Addr *p)
{
    int ret;
    if(p == NULL)
        return -1;
    ret=connect(p->fd,(struct sockaddr *)p->sockaddr,p->sockaddr_size);
    if(ret == 0)
    {
        p->tp=Addr::Addr_To_Server;
    }
    return ret;
}

int C_Socket::socket_read(C_Socket::Addr *p,void *buff,size_t count)
{
    if(p==NULL)
        return -1;
    if(p->tp==Addr::Addr_Uninitiated)
        return -1;
    int ret;
    ret=recv(p->fd,(char*)buff,count,0);
    return ret;
}

int C_Socket::socket_write(C_Socket::Addr *p,void *buff,size_t count)
{
    if(p==NULL)
        return -1;
    if(p->tp==Addr::Addr_Uninitiated)
        return -1;
    int ret;
    ret=send(p->fd,(char *)buff,count,0);
    return ret;
}

void   C_Socket::socket_server(const char * ip_addr,unsigned short ip_port,int listen_backlog,int socket_type,int socket_protocol)
{
    Addr * server = socket_new(socket_type,socket_protocol);
    if(server == NULL)
        return;
    if(ip_addr==NULL)
        socket_setaddr(server,(unsigned long)0,ip_port);
    else
        socket_setaddr(server,ip_addr,ip_port);
    if(socket_bind(server))
        {
            socket_delete(server);
            return;
        }
    if(socket_listen(server,listen_backlog))
        {
            socket_delete(server);
            return;
        }
    Addr * client=NULL;
    while(1)
    {
        client = socket_accept(server);
        if(client == NULL)
            {
            socket_delete(server);
            return;
            }
        socket_server_OnAccept(client);

    }
}

void C_Socket::socket_server_OnAccept(C_Socket::Addr * p)
{

    if(p == NULL)
    {
        return;
    }
    char * buff=new char[4096];//4K缓冲区
    int count=0;
    while(1)
    {
        count=socket_read(p,buff,4096);
        if(count>0)
        {
            socket_server_OnReceiveData(p,buff,count);
        }
        else
        {
            break;
        }
    }
    delete buff;
    socket_delete(p);
}
void C_Socket::socket_server_OnReceiveData(C_Socket::Addr *p,void *buff,size_t count)
{
    //一般用于重载，此处直接返回接收的数据。
    socket_write(p,buff,count);

}

void   C_Socket::socket_client(const char * ip_addr,unsigned short ip_port,int socket_type,int socket_protocol)
{
    Addr * server = socket_new(socket_type,socket_protocol);
    if(server == NULL)
        return;
    if(ip_addr==NULL)
        socket_setaddr(server,(unsigned long)0,ip_port);
    else
        socket_setaddr(server,ip_addr,ip_port);

    if(socket_connect(server))
    {
       socket_delete(server);
        return;
    }
    socket_client_OnConnected(server);
}
void  C_Socket::socket_client_OnConnected(Addr *p)
{
    //用于重载
    return;
}

C_Socket::~C_Socket()
{
    //dtor
    class_count--;
    if(class_count==0)
    {
        if(is_socket_init>0)
        {
            #ifdef WIN32
            if(0==WSACleanup())
                is_socket_init=0;
            #endif // WIN32

        }
    }
}

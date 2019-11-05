
#include <stdio.h>
#include <string.h>

//字符数组到Hex字符串之间的转换。
/*
out数组最好先清零以防止乱码；
成功返回0，失败返回非零
*/
int str2Hex(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{
if(in_size>((out_size)/2))
    return 1;//输出字符串空间不够
for(size_t i=0;i<in_size;i++)
    {
        unsigned char H=0,L=0;
        H=(in[i]>>4);
        L=(in[i]& 0x0f);
        if(H<=9)
            {
                out[2*i]='0'+H;
            }
        else
            {
               out[2*i]='A'+H-10;
            }
        if(L<=9)
            {
                out[2*i+1]='0'+L;
            }
        else
            {
               out[2*i+1]='A'+L-10;
            }

    }
if(in_size*2<out_size)
    {
        out[2*in_size]=0;
    }
return 0;
}

/*
out数组最好先清零以防止乱码；
成功返回0，失败返回非零
*/
int str2hex(unsigned char in[],size_t in_size,unsigned char  out[],size_t out_size)
{
if(in_size>((out_size)/2))
    return 1;//输出字符串空间不够
for(size_t i=0;i<in_size;i++)
    {
        unsigned char H=0,L=0;
        H=(in[i]>>4);
        L=(in[i]& 0x0f);
        if(H<=9)
            {
                out[2*i]='0'+H;
            }
        else
            {
               out[2*i]='a'+H-10;
            }
        if(L<=9)
            {
                out[2*i+1]='0'+L;
            }
        else
            {
               out[2*i+1]='a'+L-10;
            }

    }
if(in_size*2<out_size)
    {
        out[2*in_size]=0;
    }
return 0;
}

//大小写均支持
/*
Hex字符串转字符数组
*/
int hex2str(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{

if(in_size > out_size*2)
    return 1;//输出数组长度不够
if((in_size%2) != 0)
    return 1;//可能不是Hex字符串
for(size_t i=0;i<out_size;i++)//清空数组
    {
       out[i]=0;
    }
for(size_t i=0;i<in_size/2;i++)
    {
        unsigned char H=0,L=0;
        if(in[2*i] <= '9' && in[2*i] >= '0')
        {
            H=in[2*i]-'0';
        }
        if(in[2*i] <= 'F' && in[2*i] >= 'A')
        {
            H=in[2*i]-'A'+10;
        }
        if(in[2*i] <= 'f' && in[2*i] >= 'a')
        {
            H=in[2*i]-'a'+10;
        }

        if(in[2*i+1] <= '9' && in[2*i+1] >= '0')
        {
            L=in[2*i+1]-'0';
        }
        if(in[2*i+1] <= 'F' && in[2*i+1] >= 'A')
        {
            L=in[2*i+1]-'A'+10;
        }
        if(in[2*i+1] <= 'f' && in[2*i+1] >= 'a')
        {
            L=in[2*i+1]-'a'+10;
        }
        out[i]=((H<<4)+L);
    }

return 0;
}


int main()
{
    unsigned char in[256],out[514],in_1[256];
    for(unsigned  i=0;i<sizeof(in);i++)
    {
        in[i]=i;
        in_1[i]=0;
    }
    printf("转换结果:\n");
    str2Hex(in,sizeof(in),out,sizeof(out));
    printf("%s\n",out);
    str2hex(in,sizeof(in),out,sizeof(out));
    printf("%s\n",out);

    hex2str(out,strlen((char *)out),in_1,sizeof(in_1));
    str2Hex(in_1,sizeof(in_1),out,sizeof(out));
    printf("%s\n",out);


}

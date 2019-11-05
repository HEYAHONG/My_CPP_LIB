
#include <stdio.h>
#include <string.h>

//�ַ����鵽Hex�ַ���֮���ת����
/*
out��������������Է�ֹ���룻
�ɹ�����0��ʧ�ܷ��ط���
*/
int str2Hex(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{
if(in_size>((out_size)/2))
    return 1;//����ַ����ռ䲻��
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
out��������������Է�ֹ���룻
�ɹ�����0��ʧ�ܷ��ط���
*/
int str2hex(unsigned char in[],size_t in_size,unsigned char  out[],size_t out_size)
{
if(in_size>((out_size)/2))
    return 1;//����ַ����ռ䲻��
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

//��Сд��֧��
/*
Hex�ַ���ת�ַ�����
*/
int hex2str(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{

if(in_size > out_size*2)
    return 1;//������鳤�Ȳ���
if((in_size%2) != 0)
    return 1;//���ܲ���Hex�ַ���
for(size_t i=0;i<out_size;i++)//�������
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
    printf("ת�����:\n");
    str2Hex(in,sizeof(in),out,sizeof(out));
    printf("%s\n",out);
    str2hex(in,sizeof(in),out,sizeof(out));
    printf("%s\n",out);

    hex2str(out,strlen((char *)out),in_1,sizeof(in_1));
    str2Hex(in_1,sizeof(in_1),out,sizeof(out));
    printf("%s\n",out);


}

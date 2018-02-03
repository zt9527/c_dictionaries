#include "dirc.h"

struct data_st sigin_create(struct data_st data,int sock_fd)
{
    int send_len,recv_len;    
    while(data.sigin_flag == 0)
    {
        printf("please enter your username:");
        scanf("%s",data.username);
        printf("please enter your password:");
        scanf("%s",data.password);
        send_len = send(sock_fd,&data,sizeof(data),0);
        if(send_len < 0)
        {
            perror("send()");
            close(sock_fd);
            exit(-1);
        }
        recv_len = recv(sock_fd,&data,sizeof(data),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(sock_fd);
            exit(-1);
        }
        puts(data.msg_buf);
    }
    while(data.user_flag == 0)
    {
        printf("enter username:");
        scanf("%s",data.username);
        printf("enter password:");
        scanf("%s",data.password);
        send_len = send(sock_fd,&data,sizeof(data),0);
        if(send_len < 0)
        {
            perror("send()");
            close(sock_fd);
            exit(-1);
        }
        recv_len = recv(sock_fd,&data,sizeof(data),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(sock_fd);
            exit(-1);
        }
        puts(data.msg_buf);
    }
}

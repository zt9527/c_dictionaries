#include "dirc.h"

int main(void)
{
    int sock_fd;
    int recv_len,send_len;
    int connect_flag;
    struct data_st data,redata;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
    {
        perror("socket()");
        exit(-1);
    }
    
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);
    client_addr.sin_addr.s_addr = inet_addr("192.168.1.111");
        
    connect_flag = connect(sock_fd,(struct sockaddr *)&client_addr,sizeof(client_addr));
    if(connect_flag < 0)
    {
        perror("connect()");
        close(sock_fd);
        exit(-1);
    }
    printf("connect server sucass!!\n");
        
    data.user_flag = 1;
    data.sigin_flag = 0;
        
    sigin_create(data,sock_fd);
        
    while(1)
    {
        strcpy(redata.username,data.username);
        scanf("%s",redata.serch_word);
        int  a = strcmp(redata.serch_word,".exit");
        if(a  == 0)
        {
            close(sock_fd);
            exit(0);
        }
        
        int  b = strcmp(redata.serch_word,".chpasswd");
        if(b  == 0)
        {    
            printf("entr new password:");
            scanf("%s",redata.password);
        }
        
        int  c = strcmp(redata.serch_word,".history");
        if(c == 0)
        {
            printf("enter the data(2018-01-01):");
            scanf("%s",redata.msg_buf);
        }
        
        send_len = send(sock_fd,&redata,sizeof(redata),0);
        if(send_len < 0)
        {
            perror("send()");
            close(sock_fd);
            exit(-1);
        }
        
        recv_len = recv(sock_fd,&redata,sizeof(redata),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(sock_fd);
            exit(-1);
        }

        if(b == 0)
        {
            b = 1;
            puts(redata.msg_buf);
            exit(0);
        }
        if(c == 0)
        {
            c = 1;
            puts(redata.msg_buf);
            printf("enter serch word or \".exit\" to quit:");
        }
        else
            puts(redata.msg_buf);
    }
    close(sock_fd);
    exit(0);
}

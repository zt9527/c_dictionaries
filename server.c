#include "dirc.h"

void *pthread_hander(void *sock_fd)
{
    int recv_len,send_len;
    int new_sock_fd;
    struct data_st data,redata;
    new_sock_fd = *(int *)sock_fd;
    data.sigin_flag = 0;

    while(data.sigin_flag == 0)
    {
        recv_len = recv(new_sock_fd,&data,sizeof(data),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(new_sock_fd);
            exit(-1);
        }
        puts(data.username);
        puts(data.password);
   
        data = serch_user(data);
        puts(data.msg_buf);
        puts(data.username);
       
        send_len = send(new_sock_fd,&data,sizeof(data),0);
        if(send_len < 0)
        {
            perror("send()");
            close(new_sock_fd);
            exit(-1);
        }
    }
    while(data.user_flag == 0)
    {
        recv_len = recv(new_sock_fd,&data,sizeof(data),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(new_sock_fd);
            exit(-1);
        }
        data = insert_user(data);
        send_len = send(new_sock_fd,&data,sizeof(data),0);
        if(send_len < 0)
        {
            perror("send()");
            close(new_sock_fd);
            exit(-1);
        }
    }
    while(1)
    {
        recv_len = recv(new_sock_fd,&redata,sizeof(redata),0);
        if(recv_len < 0)
        {
            perror("recv()");
            close(new_sock_fd);
            exit(-1);
        }
        else if(recv_len == 0)
        {
            break;
        }
        strcpy(redata.username,data.username);
        int a = strcmp(redata.serch_word,".chpasswd");
        int b = strcmp(redata.serch_word,".history");
        if(a == 0)
        {
            a = 1;
            redata = chpasswd(redata);
        }
        else if(b == 0)
        {
            b = 1;
            redata = history(redata);
        }
        else
        {
            redata = serch_word(redata);
        }
        send_len = send(new_sock_fd,&redata,sizeof(redata),0);
        printf("send()\n");
        if(send_len < 0)
        {
            perror("send()");
            close(new_sock_fd);
            exit(-1);
        }
    }
    pthread_exit(0);
}

int main(void)
{
    int i = 0;
    int sock_fd;
    int new_sock_fd;
    int bind_flag,listen_flag;
    pthread_t pid[2048];
    struct data_st data,redata;
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_len;
    
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
    {
        perror("socket()");
        exit(-1);
    }
    int en = 1;
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&en,sizeof(en));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = 0;

    bind_flag = bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
    if(bind_flag < 0)
    {
        perror("bind()");
        close(sock_fd);
        exit(-1);
    }

    listen_flag = listen(sock_fd,5);
    if(listen_flag < 0)
    {
        perror("listen()");
        close(sock_fd);
        exit(-1);
    }
    
    while(1)
    {
        new_sock_fd = accept(sock_fd,(struct sockaddr *)&serv_addr,&serv_addr_len);
        if(new_sock_fd < 0)
        {
            perror("accept()");
            close(sock_fd);
            exit(-1);
        }
        pthread_create(pid+i,NULL,&pthread_hander,&new_sock_fd);
        i++;
        printf("i : %d",i);
    }
    for(int j = 0;j < i;j++)
    {
        pthread_join(pid[i-j],NULL);
    }
    pthread_join(pid[0],NULL);
    close(new_sock_fd);
    close(sock_fd);
    exit(0);
}

#ifndef DIRC_H__
#define DIRC_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sqlite3.h>

#define PORT    50565
#define USER_DB "user.db"
#define WORD_DB "dirc.db"

struct data_st
{
    char username[20];
    char password[20];
    char msg_buf[1024];
    char serch_word[20];
    int user_flag;
    int sigin_flag;
}__attribute__((packed));

struct data_st serch_user(struct data_st data);
struct data_st serch_word(struct data_st data);
struct data_st insert_user(struct data_st data);
struct data_st sigin_create(struct data_st data,int sock_fd);
struct data_st chpasswd(struct data_st data);
struct data_st history(struct data_st data);

#endif

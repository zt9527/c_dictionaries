#include "dirc.h"

struct data_st serch_user(struct data_st data)
{
    int nrow;
    int ncolnum;
    char **serch_buf;
    char cmd_buf[250];
    sqlite3 *sql_db = NULL;
    
    sqlite3_open(USER_DB,&sql_db);
    snprintf(cmd_buf,sizeof(cmd_buf),"select password from user where username = \"%s\"",data.username);
    puts(cmd_buf);
    sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
    if(nrow == 0)
    {
        data.user_flag = 0;
        data.sigin_flag = 1;
        strcpy(data.msg_buf,"don't hava this user!!\nenter username and password to create:");
        sqlite3_close(sql_db);
        return data;
    }
    
    int a = strcmp(serch_buf[1],data.password);
    printf("%d",a);
    if(a == 0)
    {
        strcpy(data.msg_buf,"holle from server!!\ncmd:.exit .chpasswd .history\nenter the word:");
        data.sigin_flag = 1;
        sqlite3_close(sql_db);
        return data;
    }
    strcpy(data.msg_buf,"password err!!");
    sqlite3_close(sql_db);
    return data;
}

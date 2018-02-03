#include "dirc.h"

struct data_st insert_user(struct data_st data)
{
    int nrow;
    int ncolnum;
    char **serch_buf;
    char cmd_buf[250];
    sqlite3 *sql_db = NULL;

    sqlite3_open(USER_DB,&sql_db);
    snprintf(cmd_buf,sizeof(cmd_buf),"select username from user where username = \"%s\"",data.username);
    sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
    if(nrow == 0)
    {
        snprintf(cmd_buf,sizeof(cmd_buf),"insert into user (username,password) values(\"%s\",\"%s\")",data.username,data.password);
        puts(cmd_buf);
        sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
        
        snprintf(cmd_buf,sizeof(cmd_buf),"create table %s (word valchar,time datetime)",data.username);
        puts(cmd_buf);
        sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
        
        strcpy(data.msg_buf,"insert sucass!!\nenter word:");
        data.user_flag = 1;
        sqlite3_close(sql_db);
        return data;
    }
    strcpy(data.msg_buf,"username hava been used!!!");
    sqlite3_close(sql_db);
    return data;
}

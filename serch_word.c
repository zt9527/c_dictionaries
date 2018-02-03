#include "dirc.h"

struct data_st serch_word(struct data_st data)
{
    int nrow;
    int ncolnum;
    char **serch_buf;
    char **insert_buf;
    char cmd_buf[250];
    sqlite3 *sql_db = NULL;
    sqlite3 *sql_user_db = NULL;
    
    sqlite3_open(WORD_DB,&sql_db);
    sqlite3_open(USER_DB,&sql_user_db);
    snprintf(cmd_buf,sizeof(cmd_buf),"select explain from dirction where word = \"%s\"",data.serch_word);
    puts(cmd_buf);
    sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
    printf("%d\n",nrow);
    if(nrow == 0)
    {
        strcpy(data.msg_buf,"don't hava this word!!");
        sqlite3_close(sql_db);
        sqlite3_close(sql_user_db);
        return data;
    }
    
    snprintf(cmd_buf,sizeof(cmd_buf),"insert into %s (word,time) values (\"%s\",datetime('now'))",data.username,data.serch_word);
    puts(cmd_buf);
    sqlite3_get_table(sql_user_db,cmd_buf,&insert_buf,&nrow,&ncolnum,NULL);
    strcpy(data.msg_buf,serch_buf[1]);
    sqlite3_close(sql_db);
    sqlite3_close(sql_user_db);
    
    return data;
}

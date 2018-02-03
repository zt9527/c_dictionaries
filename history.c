#include "dirc.h"

struct data_st history(struct data_st data)
{
    int nrow;
    int ncolnum;
    char **serch_buf;
    char cmd_buf[250];
    sqlite3 *sql_db = NULL;

    sqlite3_open(USER_DB,&sql_db);
    snprintf(cmd_buf,sizeof(cmd_buf),"select word,time from %s where time like '%s%%'",data.username,data.msg_buf);
    sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
    puts(cmd_buf);
    memset(data.msg_buf,0,sizeof(data.msg_buf));
    for(int i = 0;i < (nrow + 1)*ncolnum;i++)
    {
        strcat(data.msg_buf,serch_buf[i]);
        if((i % (ncolnum-1)) == 0)
            strcat(data.msg_buf,"\n");
    }
    puts(data.msg_buf);
    sqlite3_close(sql_db);
    return data;
}

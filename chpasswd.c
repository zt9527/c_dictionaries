#include "dirc.h"

struct data_st chpasswd(struct data_st data)
{
    int nrow;
    int ncolnum;
    char **serch_buf;
    char cmd_buf[250];
    sqlite3 *sql_db = NULL;

    sqlite3_open(USER_DB,&sql_db);
    snprintf(cmd_buf,sizeof(cmd_buf),"update user set password = \"%s\" where username = \"%s\"",data.password,data.username);
    sqlite3_get_table(sql_db,cmd_buf,&serch_buf,&nrow,&ncolnum,NULL);
    puts(cmd_buf);
    strcpy(data.msg_buf,"change password sucss!\nexit and sigin again~~");
    sqlite3_close(sql_db);
    return data;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define TXTPATH    "./dict.txt"
#define DATAPATH    "./dirc.db"
int main()
{
    FILE *fp =NULL;
    sqlite3 *db = NULL;
    char *buf = NULL;
    size_t len = 1024;
    size_t length;
    char *tokbuf = NULL;
    char cmdbuf[1024];
    char *tokbuf2 = NULL;
    buf = malloc(len);
    tokbuf = malloc(len);
    tokbuf2 = malloc(len);
    fp = fopen(TXTPATH,"r");
    sqlite3_open(DATAPATH,&db);
    while((getline(&buf,&len,fp)) != EOF)
    {
        memcpy(tokbuf,buf,len);
        tokbuf = strtok(tokbuf,"    ");
        puts(tokbuf);
        memcpy(tokbuf2,buf+17,1024);
        puts(tokbuf2);
        snprintf(cmdbuf,len,"insert into dirction (word,explain) values (\"%s\",\"%s\");",tokbuf,tokbuf2);
        sqlite3_exec(db,cmdbuf,NULL,NULL,NULL);
    }
    free(buf);
    free(tokbuf);
    free(tokbuf2);
    sqlite3_close(db);
    fclose(fp);
    exit(0);
}

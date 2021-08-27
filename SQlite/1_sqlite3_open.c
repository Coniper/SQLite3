/*******************************************************
	> File Name: 1_sqlite3_open.c
	> Author:Coniper
	> Describe: 
	> Created Time: 2021年08月25日
 *******************************************************/
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define SQSZ 128
#define NSZ 16
#define PSZ 9

int main(int argc, char *argv[])
{
    //0.定义sqlite的句柄
    sqlite3 *db;

    //1.打开或者创建数据库文件
    if(SQLITE_OK != sqlite3_open("my.db", &db))
    {
        //打印数据库操作失败的错误信息
        printf("sqlite3_open: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char *errmsg;
    //if not exists 创建数据表时自动判断是否存在，如不存在就创建，存在便不管
    char sql[SQSZ] = "create table if not exists user(id integer, name text, passwd varchar(6));";

    //执行sql语句，创建数据库表
    if(SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
        printf("create table: %s\n", errmsg);
        sqlite3_close(db);
        return -1;
    }

    char name[NSZ] = "", passwd[PSZ] = "";
    int id = 1;

    //printf("please input user name and passwd:\n");
    strcpy(name, "wx");
    strcpy(passwd, "123456");

    //将数据和sql语句放入sql数组中
    sprintf(sql, "insert into user values(%d, '%s', '%s')", id, name, passwd);
    if(SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
        printf("insert: %s\n", errmsg);
        sqlite3_close(db);
        return -1;
    }

    //关闭数据库
    sqlite3_close(db);

    return 0;
}


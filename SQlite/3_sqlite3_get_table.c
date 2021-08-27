/*******************************************************
	> File Name: 3_sqlite3_get_table.c
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

    int nrow, ncloumn;
    char **resultp;
    //将数据和sql语句放入sql数组中
    sprintf(sql, "select * from user;");
    if(SQLITE_OK != sqlite3_get_table(db, sql, &resultp, &nrow, &ncloumn, &errmsg))
    {
        printf("select: %s\n", errmsg);
        sqlite3_close(db);
        return -1;
    }
        
    //字段属于第0行，故实际有两行，resultp指向数组为:id name passwd 1 wx 123456
    printf("查询的记录条数: %d\n", nrow + 1);
    printf("每条记录的字段数: %d\n", ncloumn);
    
    int index = ncloumn;
    for(int i = 0; i < nrow; i++)
    {
        for(int j = 0; j < ncloumn; j++)
        {
            printf("%s: %s\n", resultp[j], resultp[index++]);
        }
    }
    /*
     *sqlite3_get_table函数不需要回调函数
     *参数:
     *  resultp 是一个指向指针数组的指针，用来保存查询的结果，
     *          数组中先顺序保存字段名，再顺序保存字段数值
     *
     *  nrow    保存查询结果中记录的条数(包含字段名这条记录)
     *
     *  ncloumn 保存每条记录中的字段数
     */

    //关闭数据库
    sqlite3_close(db);

    return 0;
}

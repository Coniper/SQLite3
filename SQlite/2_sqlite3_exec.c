/*******************************************************
	> File Name: 2_sqlite3_exec.c
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

/*参数：
 *      para:   要传递到回调函数的参数首地址， sqlite3_exec 函数的第 4 个参数
 *      f_num:  该条记录的字段的数目
 *      f_value:一个指向指针数组的指针, 数组中存储着 字段的数值
 *      f_name: 一个指向指针数组的指针, 数组中存储着 字段的名字
 *      注意：该回调函数是， 查询到一条记录便被调用一次！！！！！！
 *      */
int callback(void *para, int f_num, char **f_value, char **f_name); //声明回调函数

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

    //将数据和sql语句放入sql数组中
    sprintf(sql, "select * from user;");
    if(SQLITE_OK != sqlite3_exec(db, sql, callback, NULL, &errmsg))
    {
        printf("select: %s\n", errmsg);
        sqlite3_close(db);
        return -1;
    }

    //关闭数据库
    sqlite3_close(db);

    return 0;
}

int callback(void *para, int f_num, char **f_value, char **f_name)
{
    printf("记录的字段数: %d\n", f_num);
    for(int i = 0; i < f_num; i++)
    {
        printf("%s: %s\n", f_name[i], f_value[i]);
    }

    return 0;
}

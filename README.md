# 用 C 操作 SQLite3

这是我第一次把 SQLite3 的几个常用 C 接口单独拿出来练的仓库，内容不多：

- `1_sqlite3_open.c`：打开数据库；
- `2_sqlite3_exec.c`：执行 SQL、写回调；
- `3_sqlite3_get_table.c`：取出查询结果。

代码在 [SQlite](./SQlite) 目录里。我当时还把 `my.db` 一起提交了，先保留原件，后续要检查里面是否有不适合公开的数据。

这些程序只是 API 练习。真正写应用时，SQL 参数、错误处理和密码存储都要另外认真处理。

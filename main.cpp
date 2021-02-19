#include<iostream>
#include<Windows.h>
#include <mysql.h>
#include<string>


using namespace std;


int main()
{

	//必备的一个数据结构
	const char host[] = "localhost";    //or"127.0.0.1"
	const char user[] = "root";         //username
	const char pwd[] = "root";         //password
	const char db[] = "test";        //database 数据库
	unsigned int port = 3306;           //server port        
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	MYSQL_FIELD *fd;
	char column[32][32];
	int res;

	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}

	//初始化数据结构
	if (NULL != mysql_init(&myCont)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}

	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	/*if (0 == mysql_options(&myCont, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}*/

	//连接数据库的地址，用户名，密码，端口
	if (NULL != mysql_real_connect(&myCont,host,user,pwd,db,port, NULL, 0))
	{
		cout << "mysql_real_connect() succeed" << endl;
		res = mysql_query(&myCont, "select * from table_1");//查询 database下的表
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				int i, j;
				cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
				for (i = 0; fd = mysql_fetch_field(result); i++)//获取列名
				{
					printf("%s\t", fd->name);
				}/**/
				j = mysql_num_fields(result);
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					for (i = 0; i < j; i++)
					{
						printf("%s\t", sql_row[i]);
					}
					printf("\n");
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		return -1;
	}
	return 0;
}
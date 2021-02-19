#include<iostream>
#include<Windows.h>
#include <mysql.h>
#include<string>


using namespace std;


int main()
{

	//�ر���һ�����ݽṹ
	const char host[] = "localhost";    //or"127.0.0.1"
	const char user[] = "root";         //username
	const char pwd[] = "root";         //password
	const char db[] = "test";        //database ���ݿ�
	unsigned int port = 3306;           //server port        
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	MYSQL_FIELD *fd;
	char column[32][32];
	int res;

	//��ʼ�����ݿ�
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}

	//��ʼ�����ݽṹ
	if (NULL != mysql_init(&myCont)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}

	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	/*if (0 == mysql_options(&myCont, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}*/

	//�������ݿ�ĵ�ַ���û��������룬�˿�
	if (NULL != mysql_real_connect(&myCont,host,user,pwd,db,port, NULL, 0))
	{
		cout << "mysql_real_connect() succeed" << endl;
		res = mysql_query(&myCont, "select * from table_1");//��ѯ database�µı�
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				int i, j;
				cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
				for (i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
				{
					printf("%s\t", fd->name);
				}/**/
				j = mysql_num_fields(result);
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
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
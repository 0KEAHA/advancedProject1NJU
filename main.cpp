#include "ClassGen.h"


void InitialPrint();
int main()
{
	Admin* Ad = Admin::GetInstance();
	Goods* AG = Goods::GetInstance();
	Users* AU = Users::GetInstance();
	Orders* AO = Orders::GetInstance();
	AU->InputDocuUser();
	AG->InputDocuGood();
	AO->InputDocuOrder();
	while (true)
	{
		string in = "";
		InitialPrint();
		cin >> in;
		try {
			if (in.length() != 1)
				throw 1;
			if (in[0] < 49 || in[0]>52)
				throw 1;
			switch ((int)(in[0]-48))
			{
			case 1:
				Ad->Admin_login();
				break;
			case 2:	
				AU->AddUser();
				break;
			case 3:
				AU->UserLogin();
				break;
			case 4:
				return 0;
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
		}
	}
	return 0;
}

void InitialPrint()
{
	cout << "************************************************************************" << endl
		<< " 1.管理员登录       2.用户注册              3.用户登录           4.退出程序" << endl
		<< "************************************************************************" << endl
		<< endl
		<< endl
		<< "请输入操作: ";
	return;
}
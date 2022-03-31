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
		getline(cin, in);
		try {
			if (in.find(" ") != string::npos) throw 1.0;
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
		catch (double)
		{
			cout << "请不要输入空格！" << endl << endl;
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
		}
	}
	Ad->DeleteInstance();
	AG->DeleteInstance();
	AU->DeleteInstance();
	AO->DeleteInstance();
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
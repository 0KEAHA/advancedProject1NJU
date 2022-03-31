#include "User.h"


//Admin

Admin* Admin::P_Admin = nullptr;
Admin*  Admin::GetInstance()
{
	if (P_Admin == nullptr)
	{
		P_Admin = new Admin;
	}
	return P_Admin;
}
void Admin::DeleteInstance()
{
	if (P_Admin)
	{
		delete P_Admin;
		P_Admin = nullptr;
	}
	return;
}

void Admin::Admin_login()
{
	try
	{

		string Id = "";
		string password = "";
		cout << "���������Ա����: "; 
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		cout << "����������: ";
		getline(cin, password);
		if (password.find(" ") != string::npos) throw 1.0;
		cout << endl;
		if (Id == m_id && password == m_password)
		{
			cout << endl
				<< "    -----��¼�ɹ�!------" << endl
				<< endl;
			AfterLogin();
		}
		else
		{
			cout << endl
				<< "----�˺Ż��������,��½ʧ��----" << endl
				<< endl;
			return;
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
	}
}

void Admin::AfterLogin()
{
	while (true) {
		cout << "==========================================================================" << endl
			<< "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.ע��" << endl
			<< "==========================================================================" << endl
			<< endl
			<< "���������: ";
		string in = "";
		try {
			getline(cin, in);
			if (in.find(" ") != string::npos) throw 1.0;
			if (in.length() != 1)
				throw 1;
			if (in[0] < '1' || in[0]>'7')
				throw 1;
			switch ((int)(in[0] - 48))
			{
			case 1:
				AnaSQL(CheckGoods());
				break;
			case 2:
				AnaSQL(SearchGoods());
				break;
			case 3:
				AnaSQL(DisableGood());
				break;
			case 4:
				AnaSQL(CheckDeals());
				break;
			case 5:
				AnaSQL(CheckUsers());
				break;
			case 6:
				AnaSQL(DisableUser());
				break;
			case 7:
				return;
			}
		}
		catch (int)
		{
			cout << "������Ч! ��������ȷ����!" << endl;
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
		}
	}
	return;
}




//����SQLָ��



string Admin::CheckGoods()
{
	return "SELECT * FROM commodity";
}

string Admin::SearchGoods()
{
	try
	{
		cout << "��������Ʒ����: ";
		string in = "";
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		return "SELECT * FROM commodity WHERE commodityName CONTAINS " + in;
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
	}
	return"";
}

string Admin::DisableGood()
{
	try
	{
		cout << "������Ҫ�¼ܵ���ƷID: ";
		string in = "";
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (allgood->CheckGoodId(in))
		{
			if (allgood->CheckAvailable(in))
			{
				cout << "ȷ��Ҫ�¼ܸ���Ʒ��?" << endl;
				allgood->PrintGoods("Admin", "Last", "", in);
				cout << "��ѡ��(y/n):";
				string in2 = "";
				getline(cin, in2);
				if (in2.find(" ") != string::npos) throw 1.0;
				try
				{
					if (in2 == "y")
					{
						cout << "�¼ܳɹ���" << endl << endl;
						return "UPDATE commodity SET state = removed WHERE commodityID CONTAINS " + in;
					}
					if (in2 == "n")
					{
						cout << "ȡ���¼�" << endl << endl;
						return "";
					}
					else
						throw 1;
				}
				catch (int)
				{
					cout << "���벻�Ϸ�,�¼�ȡ��!" << endl << endl;
					return "";
				}
			}
			else
			{
				cout << "����Ʒ��Ϊ�¼�״̬��" << endl << endl;
				return "";
			}
		}
		else
		{
			cout << "��ƷID������,�¼�ʧ��" << endl;
			return "";
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return "";
	}
}

string Admin::CheckDeals()
{
	return "SELECT * FROM order";
}

string Admin::CheckUsers()
{
	return "SELECT * FROM user";
}

string Admin::DisableUser()
{
	cout << "������Ҫ������û�ID: ";
	string in = "";
	try
	{
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		Users* alluser = Users::GetInstance();
		if (alluser->CheckUserId(in))
		{
			if (alluser->GetUserState(in) == "inactive")
			{
				cout << "�û��ѱ����" << endl << endl;
				return "";
			}
			cout << "ȷ��Ҫ������û���?" << endl;
			cout << "*************************************************************************" << endl
				<< "�û�ID\t\t�û���\t\t��ϵ��ʽ\t\t\t��ַ\t\t\tǮ�����" << endl;
			alluser->PrintUser("AdminDisable", in);
			cout << "*************************************************************************" << endl;
			cout << "��ѡ��(y/n): ";
			string in2 = "";
			getline(cin, in2);
			if (in2.find(" ") != string::npos) throw 1.0;
			try
			{
				if (in2 == "y")
				{
					cout << "����ɹ���" << endl << endl;
					return "UPDATE user SET state = inactive WHERE sellerID CONTAINS " + in;
				}
				if (in2 == "n")
				{
					cout << "ȡ�����" << endl << endl;
					return "";
				}
				else
					throw 1;
			}
			catch (int)
			{
				cout << "���벻�Ϸ�,���ȡ��!" << endl << endl;
				return "";
			}
		}
		else
		{
			cout << "�û�ID������,���ʧ��" << endl << endl;
			return "";
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return"";
	}
}



//ִ�к���



void Admin::_CheckGoods()
{
	Goods* allgoods = Goods::GetInstance();
	allgoods->PrintGoods("Admin", "general");
	return;
}

void Admin::_SearchGoods(string contain)
{
	Goods* allgoods = Goods::GetInstance();
	allgoods->_SearchGood(contain, "Admin");
	return;
}

void Admin::_DisableGood(string Id)
{
	Goods* allgoods = Goods::GetInstance();
	allgoods->DisableGood(Id);
	return;
}

void Admin::_CheckDeals()
{
	Orders* allorder = Orders::GetInstance();
	allorder->PrintOrders("Admin");
	return;
}

void Admin::_CheckUsers()
{
	Users* allusers = Users::GetInstance();
	allusers->PrintUser("Admin");
}

void Admin::_DisableUser(string Id)
{
	Users* allusers = Users::GetInstance();
	allusers->DisaleUser(Id);
	return;
}


//User


User::User()
{
	 _UserId="";
	 _UserName="";
	 _PhoneNumber="";
	 _Address="";
	 _Password = "";
	 _UserState="";
	 _Money=0.0;
}
User::User(string Id, string name, string password)
{
	_UserId = Id;
	_Password = password;
	_UserName = name;
	_PhoneNumber = "";
	_Address = "";
	_UserState = "active";
	_Money = 0.0;
}
User::User(string Id, string name, string password, string phone, string address, string balance, string state)
{
	_UserId = Id;
	_UserName = name;
	_Password = password;
	_PhoneNumber = phone;
	_Address = address;
	_UserState = state;
	if (balance.empty()) { _Money = 0.0; }
	else { _Money = stod(balance); };
}


User& User::operator=(const User& other)
{
	if (&other != this)
	{
		_UserId = other._UserId;
		_UserName = other._UserName;
		_Password = other._Password;
		_PhoneNumber = other._PhoneNumber;
		_Address = other._Address;
		_UserState = other._UserState;
		_Money = other._Money;
	}
	return *this;
}
//С�ͺ���
string User::GetUserState()
{
	return _UserState;
}
void User::DisableUser()
{
	_UserState = "inactive";
	return;
}
void User::PrintUserDisable()
{
	string ke = to_string(_Money);
	ke.erase(ke.end() - 5, ke.end());
	cout << _UserId << "\t " << _UserName << "\t " << _PhoneNumber << "\t\t"
		<< _Address << "\t\t" << ke << endl;
	return;
}
string User::GetUserId()
{
	return _UserId;
}

bool User::CheckPass(string Password)
{
	return (Password == _Password);
}
string User::OutInfo()
{
	string ke = to_string(_Money);
	ke.erase(ke.end() - 5, ke.end());
	return _UserId + "," + _UserName + "," + _Password + "," + _PhoneNumber
		+ "," + _Address + "," +ke + "," + _UserState;
}
string User::GetUserName()
{
	return _UserName;
}
void User::PrintUserAdmin()
{
	string ke = to_string(_Money);
	ke.erase(ke.end() - 5, ke.end());
	cout << _UserId << "\t" << _UserName << "\t" << _PhoneNumber << "\t"
		<< ke << "\t";
	if (_UserState == "active")
	{
		cout << "����" << endl;
		return;
	}
	if (_UserState == "inactive")
	{
		cout << "���" << endl;
		return;
	}
}
void User::PrintUserSelf()
{
	cout << "***************************" << endl
		<< "�û����� " << _UserName << endl
		<< "��ϵ��ʽ�� " << _PhoneNumber << endl
		<< "��ַ�� " << _Address << endl
		<< "Ǯ���� " <<GetMoney() << endl
		<< "***************************" << endl<<endl;
	return;
}


//Seller


void User::AddGood(string Name, double price, int stock, string description)
{
	Goods* allgood = Goods::GetInstance();
	allgood->UpGood(_UserId, Name,price,stock,description);
	return;
}
void User::CheckMyGood()
{
	Goods* allgood = Goods::GetInstance();
	allgood->PrintGoods("Seller", "general", _UserId);
	return;
}
bool User::CheckMyGoodId(string Id)
{
	Goods* AG = Goods::GetInstance();
	if (AG->CheckGoodId(Id))
	{
		if (AG->GetSellerID(Id) == _UserId)
			return 1;
	}
	return 0;
}
void User::ChangeMyGoodPrice(string Id, double price)
{
	Goods* allgood = Goods::GetInstance();
	allgood->ChangeGoodPrice(Id, price);
	return;
}
void User::ChangeMyGoodDescrip(string Id, string description)
{
	Goods* allgood = Goods::GetInstance();
	allgood->ChangeGoodDescrip(Id, description);
	return;
}
void User::RemoveMyGood(string Id)
{
	Goods* allgood = Goods::GetInstance();
	allgood->DisableGood(Id);
	return;
}
void User::CheckMyOrder()
{
	Orders* allorder = Orders::GetInstance();
	allorder->PrintOrders("Seller", _UserId);
}


//Buyer


string User::GetMoney()
{
	ifstream in_file;
	in_file.open("recharge.txt", ios::in);
	if (!in_file)
	{
		return "0.0";
	}
	string ans = "";
	string tmp = "";
	getline(in_file, tmp);
	tmp.clear();
	getline(in_file, tmp);
	if (tmp.empty()) return "0.0";
	do
	{
		size_t pos = tmp.find(" ");
		string ke = "", ce = "";
		for (int i = 0; i < pos; i++)
		{
			ke.append(1, tmp[i]);
		}
		tmp.erase(0, pos+1);
		pos = tmp.find(" ");
		for (int i = 0; i < pos; i++)
		{
			ce.append(1, tmp[i]);
		}
		if (ke == _UserId)
		{
			ans+=(ce+"+");
		}
		ke.clear();
		ce.clear();
		tmp.clear();
	}while (getline(in_file, tmp));
	in_file.close();
	in_file.open("order.txt", ios::in);
	ans.pop_back();
	if (!in_file)
	{
		return ans;
	}
	ans += "-";
	map<string, string> consum;
	map<string, string> get;
	vector<string> Unit;
	getline(in_file, tmp);
	tmp.clear();
	while (getline(in_file, tmp))
	{
		while (tmp.find(",") != string::npos)
		{
			string ke = "";
			int pos = tmp.find(",");
			for (int i = 0; i < pos; i++)
			{
				ke.append(1, tmp[i]);
			}
			Unit.push_back(ke);
			tmp.erase(0, pos + 1);
		}
		Unit.push_back(tmp);
		tmp.clear();
		if (Unit[6] == _UserId)
		{
			consum[Unit[3]] += (Unit[2]+" ");
		}
		if (Unit[5] == _UserId)
		{
			get[Unit[3]] += (Unit[2] + " ");
		}
		Unit.clear();
	}
	if (consum.empty())
	{
		ans.pop_back();
	}
	else
	{
		string com = "(";
		for (map<string, string>::iterator it = consum.begin(); it != consum.end(); it++)
		{
			string tmp = it->second;
			string sa = "(";
			string la = "";
			for (size_t pos = tmp.find(" "); pos != string::npos; pos = tmp.find(" "))
			{
				for (int i = 0; i < pos; i++)
				{
					la.append(1, tmp[i]);
				}
				tmp.erase(0, pos + 1);
				sa += (la + "+");
				la.clear();
			}
			sa.pop_back();
			sa += ")";
			com += (it->first + "*" + sa+"+");
		}
		com.pop_back();
		com += ")";
		ans += com;
	}
	if (!get.empty())
	{
		ans += "+";
		string coming = "(";
		for (map<string, string>::iterator it = consum.begin(); it != consum.end(); it++)
		{
			string tmp = it->second;
			string sa = "(";
			string la = "";
			for (size_t pos = tmp.find(" "); pos != string::npos; pos = tmp.find(" "))
			{
				for (int i = 0; i < pos; i++)
				{
					la.append(1, tmp[i]);
				}
				tmp.erase(0, pos + 1);
				sa += (la + "+");
				la.clear();
			}
			sa.pop_back();
			sa += ")";
			coming += (it->first + "*" + sa + "+");
		}
		coming.pop_back();
		coming += ")";
		ans += coming;
	}
	if (ans.empty()) return "0.0";
	return calculator(ans);
}


void User::ChangePass(string Pass)
{
	_Password = Pass;
	return;
}
void User::CheckGood()
{
	Goods* allgood = Goods::GetInstance();
	allgood->PrintGoods("Buyer", "general");
	return;
}
void User::ChangeName(string UserName)
{
	_UserName = UserName;
	return;
}
void User::ChangeAddress(string Add)
{
	_Address = Add;
	return;
}
void User::ChangePhone(string Phone)
{
	_PhoneNumber = Phone;
	return;
}
void User::AddMoney(double add)
{
	_Money += add;
	return;
}

void User::BuyGood(string OrderId, string GoodId, string Price, string Num, string Date, string SellerId)
{
	Orders* allorder = Orders::GetInstance();
	allorder->UpOrder(OrderId, GoodId, Price, Num, Date, SellerId, _UserId);
	Goods* allgood = Goods::GetInstance();
	allgood->SellGood(GoodId, stoi(Num));
	return;
}
void User::SearchGood(string name)
{
	Goods* allgood = Goods::GetInstance();
	allgood->_SearchGood(name,"Buyer");
	return;
}
void User::CheckOrder()
{
	Orders* allorder = Orders::GetInstance();
	allorder->PrintOrders("Buyer", "", _UserId);
	return;
}
void User::CheckGoodAccura(string Id)
{
	Goods* allgood = Goods::GetInstance();
	allgood->PrintGoods("Buyer", "specific", "",Id);
	return;
}




//Users   All


Users* Users::P_AllUsers = nullptr;
Users* Users::GetInstance()
{
	if (P_AllUsers == nullptr)
	{
		P_AllUsers = new Users;
	}
	return P_AllUsers;
}
void Users::DeleteInstance()
{
	if (P_AllUsers != nullptr)
	{
		delete P_AllUsers;
		P_AllUsers = nullptr;
	}
	return;
}



//�ļ�����

void Users::InputDocuUser()
{
	ifstream in_file;
	in_file.open("user.txt",
		ios::in);
	if (!in_file)
	{
		ofstream out_file;
		out_file.open("user.txt",
			ios::out);
		out_file.close();
		return;
	}
	AllUsers.clear(); 
	vector<string> Unit;
	string tmp = "";
	getline(in_file, tmp);
	tmp.clear();
	while (getline(in_file, tmp))
	{
		while (tmp.find(",") != string::npos)
		{
			string ke = "";
			int pos = tmp.find(",");
			for (int i = 0; i < pos; i++)
			{
				ke.append(1, tmp[i]);
			}
			Unit.push_back(ke);
			tmp.erase(0, pos + 1);
		}
		Unit.push_back(tmp);
		tmp.clear();
		User A(Unit[0], Unit[1], Unit[2], Unit[3], Unit[4], Unit[5], Unit[6]);
		AllUsers[Unit[0]] = A;
		Unit.clear();
	}
	if (in_file.eof())
	{
		in_file.close();
	}
	else
	{
		cout << "Read User txt Wrong!" << endl;
	}
	return;
}

void Users::ResetDocuUser()
{
	ofstream out_file;
	out_file.open("user.txt", ios::out);
	if (out_file.fail())
	{
		cout << "Open user.txt to write Error!" << endl;
		exit(-1);
	}
	out_file << "userID,username,password,phoneNumber,address,balance,userState";
	if (AllUsers.empty() != true)
	{
		out_file << endl;
		map<string,User>::iterator it = AllUsers.begin();
		auto mmm = AllUsers.end();
		--mmm;
		while (it != mmm)
		{
			out_file << it->second.OutInfo() << endl;
			it++;
		}
		out_file << it->second.OutInfo();
	}
	out_file.close();
	InputDocuUser();
	return;
}




// С����




User* Users::GetPUser()
{
	return _CurrUser;
}
string Users::GetUserState(string Id)
{
	return AllUsers[Id].GetUserState();
}
int Users::GetAll()
{
	int num = 0;
	for (map<string,User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
	{
		num++;
	}
	return num;
}
void Users::AddUser()
{
	try
	{
		string UserId = "";
		string Pass = "";
		cout << "�������û����� ";
		getline(cin, UserId);
		if (UserId.find(" ") != string::npos|| UserId.find(",") != string::npos) throw 1.0;
		if (UserId.length() > 10) 
		{
			cout << "�û�����������С��ʮһ����ĸ��" << endl << endl; return;}
		for (string::iterator it = UserId.begin(); it != UserId.end(); it++)
		{
			if (*it < 'A' || *it>'z' || (*it > 'Z' && *it < 'a')) {
				cout << "----������Ӣ����ĸ�����˳�ע��----" << endl << endl;
				return;
			}
		}
		cout << "���������룺 "; 
		getline(cin, Pass);
		for (string::iterator it = Pass.begin(); it != Pass.end(); it++)
		{
			if ((*it < 'a' && (*it < '0' || *it>'9')) || *it > 'z')
			{
				cout << "----������Сд��ĸ�����֣����˳�ע��----" << endl << endl;
				return;
			}
		}
		if (Pass.find(" ") != string::npos|| Pass.find(",") != string::npos) throw 1.0;
		if (CheckUserName(UserId))
		{
			cout << "----�û����Ѵ��ڣ��˳�ע��----" << endl << endl;
			return;
		}
		else
		{
			string newPass;
			newPass.clear();
			cout << "���ٴ�ȷ�����룺";
			getline(cin, newPass);
			if (newPass == Pass)
			{
				int k = GetAll() + 1;
				string tp = "";
				for (int i = 100; i >= 1; i /= 10)
				{
					tp += to_string(k / i);
					k %= i;
				}
				string ke = "U" + tp;
				AllUsers[ke] = User(ke, UserId, Pass);
				ResetDocuUser();
				cout << "-----ע��ɹ�,�������������¼----" << endl << endl;
			}
			else
			{
				cout << "�������벻һ�£����˳�ע�ᣡ" << endl << endl;
			}
			return;
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո���߶��ţ�" << endl << endl;
		return;
	}
}

void Users::UserLogin()
{
	try
	{
		string UserId = "";
		string Pass = "";
		cout << "�������û����� ";
		getline(cin, UserId);
		if (UserId.find(" ") != string::npos) { throw 1.0; }
		cout << "���������룺 "; 
		getline(cin, Pass);
		if (Pass.find(" ") != string::npos) { throw 1.0; }
		if (!CheckUserName(UserId))
		{
			cout << "----�û������ڣ�----" << endl << endl;
			_CurrUser = nullptr;
			return;
		}
		else
		{
			_CurrUser = &AllUsers[GetUserId(UserId)];
			if (_CurrUser->GetUserState() == "inactive")
			{
				cout << "���ѱ������" << endl << endl;
				return;
			}
			if (_CurrUser->CheckPass(Pass))
			{
				cout << "----��¼�ɹ���----" << endl << endl;
				Carts* AllCart = Carts::GetInstance();
				AllCart->SetUserId(GetUserId(UserId));
				AfterLogin();
				return;
			}
			else
			{
				cout << "----������������µ�¼��----" << endl << endl;
				return;
			}
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return;
	}
}
bool Users::CheckUserId(string Id)
{
	for (map<string, User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
	{
		if (it->second.GetUserId() == Id)
			return 1;
	}
	return 0;
}
bool Users::CheckUserName(string name)
{
	for (map<string,User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
	{
		if (it->second.GetUserName() == name)
			return 1;
	}
	return 0;
}
string Users::GetUserId(string Name)
{
	for (map<string,User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
	{
		if (it->second.GetUserName() == Name)
			return it->second.GetUserId();
	}
	return "";
}

void Users::PrintUser(string commander, string Id)
{
	
	if (commander == "Admin")
	{
		cout << "***************************************************************************************************" << endl;
		cout << "�û�ID\t�û���\t��ϵ��ʽ\t\t��ַ\t\tǮ�����\t�û�״̬" << endl;
		for (map<string,User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
		{
			it->second.PrintUserAdmin();
		}
		cout << "***************************************************************************************************" << endl;
		return;
	}
	else if (commander == "AdminDisable")
	{
		AllUsers[Id].PrintUserDisable();
		
		return;
	}
	else if (commander == "UserSelf")
	{
		AllUsers[Id].PrintUserSelf();
		return;
	}
	else
	{
		cout << "The commander parameter of PrintUsert is Wrong!" << endl;
		cout << "***************************************************************************************************" << endl;
		return;
	}
}

void Users::DisaleUser(string Id)
{
	AllUsers[Id].DisableUser();
	ResetDocuUser();
	return;
}


void Users::AfterLogin()
{
	while (true)
	{
		cout << "=================================================" << endl
			<< "1.�������  2.��������  3.������Ϣ���� 4.ע����¼" << endl
			<< "=================================================" << endl << endl;
		string in = "";
		cout << "����������� ";
		getline(cin,in);
		try
		{
			if (in.find(" ") != string::npos) throw 1.0;
			if (in.length() != 1)
			{
				throw 1;
			}
			if (in[0] < '1' || in[0]>'4')
			{
				throw 1;
			}
			else
			{
				switch ((int)(in[0] - 48))
				{
				case 1:
					UserBuyer();
					break;
				case 2:
					UserSeller();
					break;
				case 3:
					Me();
					break;
				case 4:
					return;
				}
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl<<endl;
			break;
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
			break;
		}
	}
}




//���Ҳ���


void Users::UserSeller()
{
	while (true)
	{
		cout << "===========================================================================" << endl
			<< "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl
			<< "===========================================================================" << endl << endl;
		string in = "";
		cout << "����������� "; 
		getline(cin, in);
		try
		{
			if (in.find(" ") != string::npos) throw 1.0;
			if (in.length() != 1)
			{
				throw 1;
			}
			if (in[0] < '1' || in[0]>'6')
			{
				throw 1;
			}
			else
			{
				switch ((int)(in[0] - 48))
				{
				case 1:
					_CurrUser->AnaSQL(AddGood());
					break;
				case 2:
					_CurrUser->AnaSQL(CheckMyGood());
					break;
				case 3:
					_CurrUser->AnaSQL(ChangeMyGood());
					break;
				case 4:
					_CurrUser->AnaSQL(RemoveMyGood());
					break;
				case 5:
					_CurrUser->AnaSQL(CheckMyOrder());
					break;
				case 6:
					return;
				}
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
			continue;
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
			continue;
		}
	}
	return;
}

string Users::AddGood()
{
	try
	{
		string GoodName = "", Price = "", Stock = "", Descrip = "";
		cout << "��������Ʒ���ƣ� ";
		getline(cin, GoodName);
		if (GoodName.find(" ") != string::npos|| GoodName.find(",") != string::npos) throw 1.0;
		for (string::iterator it = GoodName.begin(); it != GoodName.end(); it++)
		{
			if (*it < 'A' || *it>'z' || (*it > 'Z' && *it < 'a'))
			{
				cout << "----������Ӣ����ĸ�����˳�����----" << endl << endl;
				return"";
			}
		}
		cout << "��������Ʒ�۸� ";
		getline(cin, Price);
		if (Price.find(" ") != string::npos) throw 1.0;
		cout << "��������Ʒ������ ";
		getline(cin, Stock);
		if (Stock.find(" ") != string::npos|| Stock.find(",") != string::npos) throw 1.0;
		cout << "��������Ʒ������ "; 
		getline(cin, Descrip);
		string::iterator it;
		it = Price.begin();
		if (GoodName.length() > 20)
		{
			cout << "---�������ƹ�����������21���ַ�---" << endl << endl;
			return "";
		}
		try
		{
			if (Price[0] < '0' || Price[0]>'9') throw 1;
			if (Price[0] == '0' && (Price[1] != '.')) throw 1;
			for (int i = 1; i < Price.length(); i++)
			{
				if (Price[i] < '0' || Price[i]>'9')
				{
					if (Price[i] == '.')
					{
						if (i == Price.length() - 2 && (Price[i + 1] >= '0' || Price[i + 1] <= '9'))
						{
							break;
						}
						else throw 1;
					}
					else throw 1;
				}
			}
		}
		catch (int)
		{
			cout << "---�۸��ʽ����ȷ�����˳���������ȷ����������һλС��������---" << endl << endl;
			return "";
		}
		try
		{
			if (Stock[0] < '1' || Stock[0]>'9') throw 1;
			for (int i = 1; i < Stock.length(); i++)
			{
				if (Stock[i] < '0' || Stock[i]>'9')
				{
					throw 1;
				}
			}
		}
		catch (int)
		{
			cout << "---������ʽ����ȷ��������������---" << endl << endl;
			return "";
		}
		if (Descrip.length() > 200)
		{
			cout << "----������������,���˳�����----" << endl << endl;
			return "";
		}
		if (Descrip.find(",") != string::npos)
		{
			cout << "----�������������� \",\" ���˳�����----" << endl << endl;
			return"";
		}
		cout << "�ϼܳɹ���" << endl << endl;
		return "INSERT INTO commodity VALUES ( " + GoodName + " " + Price + " "
			+ Stock + " " + Descrip + " )";
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո���߶��ţ�" << endl << endl;
		return"";
	}
}

string Users::CheckMyGood()
{
	return "SELECT * FROM commodity";
}
string Users::ChangeMyGood()
{
	try
	{
		string GoodId = "", Price = "", Descrip = "",Stock="";
		string in;
		cout << "�����뱻�޸ĵ���Ʒ��ID�� ";
		getline(cin, GoodId);
		if (GoodId.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (!allgood->CheckGoodId(GoodId))
		{
			cout << "��ƷID������!" << endl << endl;
			return "";
		}
		cout << "�����뱻�޸ĵ���Ʒ������ ��1.�۸� 2.���� 3.��� 4.ȡ��): ";
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		Goods* all = Goods::GetInstance();
		try
		{
			if (in.length() != 1)
			{
				throw 1;
			}
			if (in[0] < '1' || in[0]>'4')
			{
				throw 1;
			}
			else
			{
				switch ((int)(in[0] - 48))
				{
				case 1:
					cout << "�����뱻�޸���Ʒ�ļ۸�: ";
					getline(cin, Price);
					if (Price.find(" ") != string::npos) throw 1.0;
					try
					{
						if (Price[0] < '0' || Price[0]>'9') throw 1;
						if (Price[0] == '0' && (Price[1] != '.')) throw 1;
						for (int i = 1; i < Price.length(); i++)
						{
							if (Price[i] < '0' || Price[i]>'9')
							{
								if (Price[i] == '.')
								{
									if (i == Price.length() - 2 && (Price[i + 1] >= '0' || Price[i + 1] <= '9'))
									{
										break;
									}
									else throw 1;
								}
								else throw 1;
							}
						}
					}
					catch (int)
					{
						cout << "---�۸��ʽ����ȷ�����˳��޸ģ���ȷ�޸�������һλС��������---" << endl << endl;
						return "";
					}
					cout << "��ȷ�ϱ��޸ĵ���Ʒ��Ϣ����!" << endl;

					all->PrintWhenChange(GoodId, "Price", Price);
					cout << "ȷ���޸�? (y/n)";
					in.clear();
					getline(cin, in);
					if (in.find(" ") != string::npos) throw 1.0;
					if (in == "y")
					{
						return ("UPDATE commodity SET price = " + Price + " WHERE commodityID CONTAINS " + GoodId);
					}
					if (in == "n")
					{
						cout << "ȡ���޸�!" << endl << endl;
						return"";
					}
					else
					{
						cout << "Invalid Input" << endl << endl;
						return "";
					}
				case 2:
					cout << "�����뱻�޸���Ʒ������: ";
					getline(cin, Descrip);
					if (Descrip.length() > 200)
					{
						cout << "----������������,���˳��޸�----" << endl << endl;
						return "";
					}
					if (Descrip.find(",") != string::npos)
					{
						cout << "----���������� \",\" ���˳��޸�----" << endl << endl;
						return"";
					}
					else
					{
						cout << "��ȷ�ϱ��޸ĵ���Ʒ��Ϣ����!" << endl;

						all->PrintWhenChange(GoodId, "Descrip", Descrip);
						cout << "ȷ���޸�? (y/n)";
						in.clear();
						getline(cin, in);
						if (in.find(" ") != string::npos) throw 1.0;
						if (in == "y")
						{
							return "UPDATE commodity SET description = " + Descrip + " WHERE commodityID CONTAINS " + GoodId;
						}
					}
					break;
				case 3:
					cout << "�������޸ĺ���Ʒ������";
					getline(cin, Stock);
					if (Stock[0] < '1' || Stock[0]>'9') throw 1;
					for (int i = 1; i < Stock.length(); i++)
					{
						if (Stock[i] < '0' || Stock[i]>'9')
						{
							throw 1;
						}
					}
					allgood->ChangeGoodStock(GoodId, stoi(Stock));
					cout << "�޸ĳɹ���" << endl << endl;
					break;
				case 4:
					return"";
				}
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
			return "";
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
			return"";
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return"";
	}
	return "";
}

string Users::RemoveMyGood()
{
	try
	{
		string Id = "";
		cout << "������Ҫ�¼ܵ���ƷID: ";
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (_CurrUser->CheckMyGoodId(Id))
		{
			cout << "ȷ��Ҫ�¼ܸ���Ʒ��?" << endl;
			allgood->PrintGoods("Seller", "Last", "", Id);
			cout << "��ѡ��(y/n): ";
			string in = "";
			getline(cin, in);
			if (in.find(" ") != string::npos) throw 1.0;
			if (in == "y")
			{
				return "UPDATE commodity SET state = removed WHERE commodityID CONTAINS " + Id;
			}
			if (in == "n")
			{
				cout << "ȡ���¼�" << endl << endl;
				return "";
			}
			else
			{
				cout << "Invalid Input!" << endl << endl;
				return "";
			}
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return"";
	}
	return"";
}

string Users::CheckMyOrder()
{
	return "SELECT * FROM order";
}




//��ҹ���  BUYER



void Users::UserBuyer()
{
	Carts* AllCart = Carts::GetInstance();
	while (true)
	{
			cout << "=========================================================================================================" << endl
				<< "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����ﳵ 7.�����û�������" << endl
				<< "=========================================================================================================" << endl << endl;
			cout << "����������� ";
			string in = "";
			getline(cin, in);
			try
			{
				if (in.find(" ") != string::npos) throw 1.0;
				if (in.length() > 1)
				{
					throw 1;
				}
				if (in[0] < '1' || in[0]>'7') throw 1;
				switch ((int)(in[0] - 48))
				{
				case 1:
					_CurrUser->SPAnaSQL(CheckGood());
					break;
				case 2:
					_CurrUser->SPAnaSQL(BuyGood());
					break;
				case 3:
					_CurrUser->SPAnaSQL(SearchGood());
					break;
				case 4:
					_CurrUser->SPAnaSQL(CheckOrder());
					break;
				case 5:
					_CurrUser->SPAnaSQL(CheckGoodAccura());
					break;
				case 6:
					AllCart->GovCarts();
					break;
				case 7:
					return;
				}
			}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
			continue;
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
			continue;
		}
	}
	return;
}

string Users::CheckGood()
{
	return "SELECT * FROM commodity";
}
string Users::BuyGood()
{
	try
	{
		string Id = "", Stock = "";
		cout << "��������Ʒ ID�� ";
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (!allgood->CheckGoodId(Id))
		{
			cout << "��ƷID�����ڣ�" << endl << endl;
			return"";
		}
		cout << "�����빺��������";
		getline(cin, Stock);
		if (Stock.find(" ") != string::npos) throw 1.0;
		try
		{
			if (Stock[0] < '1' || Stock[0]>'9') throw 1;
			for (int i = 1; i < Stock.length(); i++)
			{
				if (Stock[i] < '0' || Stock[i]>'9')
					throw 1;
			}
		}
		catch (int)
		{
			cout << "---������ʽ����ȷ��������������---" << endl << endl;
			return "";
		}
		int integer = stoi(Stock);
		if (integer > allgood->GetGoodStock(Id))
		{
			cout << "��Ʒ��治�㣡" << endl << endl;
			return"";
		}
		string _UpTime = "";
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		_UpTime = to_string(timeinfo->tm_year + 1900) + "-";
		if (timeinfo->tm_mon < 10) _UpTime += "0";
		_UpTime += (to_string(timeinfo->tm_mon + 1) + "-");
		if (timeinfo->tm_mday < 10) _UpTime += "0";
		_UpTime += to_string(timeinfo->tm_mday);
		Orders* allorder = Orders::GetInstance();
		int k = allorder->GetAll() + 1;
		string tp = "";
		for (int i = 100; i >= 1; i /= 10)
		{
			tp += to_string(k / i);
			k %= i;
		}
		string OrderId = "T" + tp;
		return "INSERT INTO order VALUES ( " + OrderId + "," + Id + "," + allgood->GetPrice(Id)
			+ "," + Stock + "," + _UpTime + "," + allgood->GetSellerID(Id) + ","
			+ _CurrUser->GetUserId() + " )";
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
		return"";
	}
}

string Users::SearchGood()
{
	try
	{
		string Name;
		cout << "��������Ʒ����: ";
		getline(cin, Name);
		if (Name.find(" ") != string::npos) throw 1.0;
		return "SELECT * FROM commodity WHERE commodityName  CONTAINS " + Name;
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl;
		return "";
	}
}
string Users::CheckOrder()
{
	return "SELECT * FROM order";
}
string Users::CheckGoodAccura()
{
	try
	{
		cout << "����������Ҫ�鿴����ƷID: ";
		string Id = "";
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (allgood->CheckGoodId(Id))
		{
			return "SELECT * FROM commodity WHERE commodityID CONTAINS " + Id;
		}
		else
		{
			cout << "��ƷID�����ڣ�" << endl;
			return"";
		}
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl;
		return"";
	}
}

void Users::Me()
{
	while (true)
	{
		cout << "=================================================" << endl
			<< "1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������" << endl
			<< "=================================================" << endl << endl;
		cout << "����������� ";
		string in = "";
		getline(cin, in);
		try
		{
			if (in.find(" ") != string::npos) throw 1.0;
			if (in.length() > 1)
			{
				throw 1;
			}
			if (in[0] < '1' || in[0]>'6') throw 1;
			switch ((int)(in[0] - 48))
			{
			case 1:
				PrintUser("UserSelf", _CurrUser->GetUserId());
				break;
			case 2:
				ChangeMe();
				break;
			case 3:
				AddMoney();
				break;
			case 4:
				return;
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
		}
		catch (double)
		{
			cout << "�벻Ҫ����ո�" << endl << endl;
		}
	}
}

void Users::ChangeMe()
{
	string in;
	cout << "��ѡ���޸ĵ����� ��1.�û��� 2.��ϵ��ʽ 3.��ַ 4.���� 5.�˳�����";
	getline(cin,in);
	try
	{
		if (in.find(" ") != string::npos) throw 1.0;
		if (in.length() > 1)
		{
			throw 1;
		}
		if (in[0] < '1' || in[0]>'5') throw 1;
		string aka = "";
		string pa = "";
		switch ((int)(in[0] - 48))
		{
		case 1:
			while (true)
			{
				try
				{
					cout << "�������޸ĺ���û����� ";
					getline(cin,aka);
					if (aka.find(" ") != string::npos || aka.find(",") != string::npos)
					{
						throw 1.0;
					}
					for (map<string, User>::iterator it = AllUsers.begin(); it != AllUsers.end(); it++)
					{
						if (it->second.GetUserName() == aka)
						{
							throw 1;
						}
					}
					_CurrUser->ChangeName(aka);
					ResetDocuUser();
					cout << "�޸ĳɹ���" << endl << endl;
					break;
				}
				catch (int)
				{
					cout << "�û����Ѵ��ڣ�����������" << endl;
				}
				catch (double)
				{
					cout << "�벻Ҫ����ո���߶��ţ�" << endl << endl;
				}

			}
			break;
		case 2:
			cout << "�������޸ĺ����ϵ��ʽ�� ";
			try {
				getline(cin, aka);
				if (aka.find(" ") != string::npos || aka.find(",") != string::npos)
				{
					throw 1;
				}
				_CurrUser->ChangePhone(aka);
				ResetDocuUser();
				cout << "�޸ĳɹ���" << endl << endl;
				break;
			}
			catch (int)
			{
				cout << "�벻Ҫ����ո���߶��ţ�" << endl << endl;
			}
			break;
		case 3:
			cout << "�������޸ĺ�ĵ�ַ�� ";
			getline(cin, aka);
			try {
				if (aka.find(" ") != string::npos || aka.find(",") != string::npos)
				{
					throw 1;
				}
				for (string::iterator it = aka.begin(); it != aka.end(); it++)
				{
					if (*it < 'A' || *it>'z' || (*it > 'Z' && *it < 'a'))
					{
						cout << "----������Ӣ����ĸ�����˳�ע��----" << endl << endl;
						return;
					}
				}
				_CurrUser->ChangeAddress(aka);
				ResetDocuUser();
				cout << "�޸ĳɹ���" << endl << endl;
				break;
			}
			catch (int)
			{
				cout << "�벻Ҫ����ո���߶��ţ�" << endl << endl;
			}
			break;
		case 4:
			cout << "������ԭ���룺 ";
			getline(cin, pa);
			if (_CurrUser->CheckPass(pa))
			{
				while (true)
				{
					cout << "�����������룺";
					pa.clear();
					getline(cin, pa);
					if (_CurrUser->CheckPass(pa))
					{
						cout << "�����벻����ԭ������ͬ��" << endl;
						continue;
					}
					else
					{
						string newpa;
						cout << "���ٴ����������룺" << endl;
						getline(cin, newpa);
						if (newpa == pa)
						{
							_CurrUser->ChangePass(pa);
							ResetDocuUser();
							cout << "�޸ĳɹ���" << endl << endl;
							break;
						}
						else
						{
							cout << "�������벻һ�£��������޸�" << endl << endl;
							continue;
						}
					}
				}
			}
			else
			{
				cout << "��������������˳��޸�" << endl << endl;
			}
			break;
		case 5:
			return;
		}
	}
	catch (int)
	{
		cout << "Invalid Input!" << endl << endl;
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
	}
	return;
}

void Users::AddMoney()
{
	cout << "�������ֵ�� ";
	string Price= "";
	getline(cin, Price);
	try
	{
		if (Price.find(" ") != string::npos) throw 1.0;
		if (Price[0] < '0' || Price[0]>'9') throw 1;
		if (Price[0] == '0' && (Price[1] != '.')) throw 1;
		for (int i = 1; i < Price.length(); i++)
		{
			if (Price[i] < '0' || Price[i]>'9')
			{
				if (Price[i] == '.')
				{
					if (i == Price.length() - 2 && (Price[i+1] >= '0' || Price[i+1] <= '9'))
					{
						break;
					}
					else throw 1;
				}
				else throw 1;
			}
		}
	}
	catch (int)
	{
		cout << "---����ȷ����ֵʧ�ܣ�������һλС��������---" << endl << endl;
		return ;
	}
	catch (double)
	{
		cout << "�벻Ҫ����ո�" << endl << endl;
	}
	_CurrUser->AddMoney(stod(Price));
	ofstream out_file;
	out_file.open("recharge.txt", ios::app);
	out_file << endl<< _CurrUser->GetUserId() << " " << Price<<" " ;
	cout << "��ֵ�ɹ�����ǰ�� " << _CurrUser->GetMoney() << endl;
	ResetDocuUser();
	return;
}
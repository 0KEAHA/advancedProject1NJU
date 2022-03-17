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
	string Id = "";
	string password = "";
	cout << "���������Ա����: "; cin >> Id;
	cout << "����������: "; cin >> password; cout << endl;
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
			cin >> in;
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
	cout << "��������Ʒ����: ";
	string in = "";
	cin >> in;
	return "SELECT * FROM commodity WHERE commodityName CONTAINS " + in;
}

string Admin::DisableGood()
{
	cout << "������Ҫ�¼ܵ���ƷID: ";
	string in = "";
	cin >> in;
	Goods* allgood = Goods::GetInstance();
	if (allgood->CheckGoodId(in))
	{
		cout << "ȷ��Ҫ�¼ܸ���Ʒ��?" << endl;
		allgood->PrintGoods("Admin", "Last", "", in);
		cout << "��ѡ��(y/n):";
		string in2 = "";
		cin >> in2;
		try
		{
			if (in2 == "y")
			{
				return "UPDATE commodity SET state = removed WHERE commodityID CONTAINS " + in2;
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
		cout << "��ƷID������,�¼�ʧ��" << endl;
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
	cin >> in;
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
		cin >> in2;
		try
		{
			if (in2 == "y")
			{
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
		cout << "�û�ID������,���ʧ��" << endl <<endl;
		return "";
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
	_Money = stod(balance);
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
	cout << _UserId << "\t  " << _UserName << "\t  " << _PhoneNumber << "\t\t"
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
	string ke = to_string(_Money);
	ke.erase(ke.end() - 5, ke.end());
	cout << "***************************" << endl
		<< "�û����� " << _UserName << endl
		<< "��ϵ��ʽ�� " << _PhoneNumber << endl
		<< "��ַ�� " << _Address << endl
		<< "Ǯ���� " << ke << endl
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
	in_file.open("E:\\Project 1\\Project 1\\recharge.txt", ios::in);
	if (!in_file)
	{
		return "0.0";
	}
	string ans = "";
	string tmp = "";
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
	in_file.open("E:\\Project 1\\Project 1\\order.txt", ios::in);
	ans.pop_back();
	if (!in_file)
	{
		return ans;
	}
	ans += "-";
	map<string, string> consum;
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
		Unit.clear();
	}
	if (consum.empty())
	{
		ans.pop_back();
	}
	else
	{
		for (map<string, string>::iterator it = consum.begin(); it != consum.end(); it++)
		{
			string sa = "(";
			string la = "";
			for (size_t pos = it->second.find(" "); pos != string::npos; pos = it->second.find(" "))
			{
				for (int i = 0; i < pos; i++)
				{
					la.append(1, tmp[i]);
				}
				sa += (la + "+");
			}
			sa.pop_back();
			sa += ")+";
			ans += sa;
		}
		ans.pop_back();
	}
	if (ans.empty()) return "0.0";
	return calculator(ans);
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
	in_file.open("E:\\Project 1\\Project 1\\user.txt",
		ios::in);
	if (!in_file)
	{
		ofstream out_file;
		out_file.open("E:\\Project 1\\Project 1\\user.txt",
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
		AllUsers[Unit[0]] = User(Unit[0], Unit[1], Unit[2], Unit[3], Unit[4], Unit[5], Unit[6]);
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
	out_file.open("E:\\Project 1\\Project 1\\user.txt", ios::out);
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
		while (it != AllUsers.end())
		{
			out_file << it->second.OutInfo() << endl;
			it++;
		}
	}
	out_file.close();
	InputDocuUser();
	return;
}




// С����





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
	string UserId = "";
	string Pass = "";
	cout << "�������û����� "; cin >> UserId;
	cout << "���������룺 "; cin >> Pass;
	if (CheckUserName(UserId))
	{
		cout << "----�û����Ѵ��ڣ��˳�ע��----" << endl << endl;
		return;
	}
	else
	{
		string ke = "U" + to_string(GetAll());
		AllUsers[ke] = User(ke, UserId, Pass);
		ResetDocuUser();
		cout << "-----ע��ɹ�,�������������¼----" << endl << endl;
		return;
	}
}

void Users::UserLogin()
{
	string UserId = "";
	string Pass = "";
	cout << "�������û����� "; cin >> UserId;
	cout << "���������룺 "; cin >> Pass;
	if (!CheckUserName(UserId))
	{
		cout << "----�û������ڣ�----" << endl <<endl;
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
				AfterLogin();
				return;
			}
			else
			{
				cout << "----������������µ�¼��----" << endl<<endl;
				return;
			}
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
		cout << "***************************************************************************************************" << endl;
		cout << "�û�ID\t�û���\t��ϵ��ʽ\t\t��ַ\t\tǮ�����" << endl;
		AllUsers[Id].PrintUserDisable();
		cout << "***************************************************************************************************" << endl;
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
		cout << "����������� "; cin >> in;
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
		cout << "����������� "; cin >> in;
		try
		{
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
		}
	}
	return;
}

string Users::AddGood()
{
	string GoodName = "",Price="",Stock="",Descrip="";
	cout << "��������Ʒ���ƣ� "; cin >> GoodName;
	cout << "��������Ʒ�۸� "; cin >> Price;
	cout << "��������Ʒ������ "; cin >> Stock;
	cout << "��������Ʒ������ "; cin >> Descrip;
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
		for (int i = 1; i <Price.length(); i++)
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
		cout << "---�۸��ʽ����ȷ�����˳���������ȷ����������һλС��������---" << endl << endl;
		return "";
	}
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
	return "INSERT INTO commodity VALUES ( " + GoodName + " " + Price + " "
		+ Stock + " " + Descrip + " )";
}

string Users::CheckMyGood()
{
	return "SELECT * FROM commodity";
}
string Users::ChangeMyGood()
{
	string GoodId = "",Price="",Descrip="";
	string in;
	cout << "�����뱻�޸ĵ���Ʒ��ID�� "; cin >> GoodId;
	Goods* allgood = Goods::GetInstance();
	if (!allgood->CheckGoodId(GoodId))
	{
		cout << "��ƷID������!" << endl << endl;
		return "";
	}
	cout << "�����뱻�޸ĵ���Ʒ������ ��1.�۸� 2.����): ";
	cin >> in;
	Goods* all = Goods::GetInstance();
	try
	{
		if (in.length() != 1)
		{
			throw 1;
		}
		if (in[0] < '1' || in[0]>'2')
		{
			throw 1;
		}
		else
		{
			switch ((int)(in[0] - 48))
			{
			case 1:
				cout << "�����뱻�޸���Ʒ�ļ۸�: ";
				cin>>Price;
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
					cout << "---�۸��ʽ����ȷ�����˳��޸ģ���ȷ�޸�������һλС��������---" << endl << endl;
					return "";
				}
				cout << "��ȷ�ϱ��޸ĵ���Ʒ��Ϣ����!" << endl;
				
				all->PrintWhenChange(GoodId,"Price",Price);
				cout << "ȷ���޸�? (y/n)";
				in.clear();
				cin >> in;
				if (in == "y")
				{
					return ("UPDATE commodity SET price = "+Price+" WHERE commodityID CONTAINS "+GoodId);
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
				cin>>Descrip;
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
					
					all->PrintWhenChange(GoodId,"Descrip",Descrip);
					cout << "ȷ���޸�? (y/n)";
					in.clear();
					cin >> in;
					if (in == "y")
					{
						return "UPDATE commodity SET description = " + Descrip + " WHERE commodityID CONTAINS " + GoodId;
					}
				}
				break;
			}
		}
	}
	catch (int)
	{
		cout << "Invalid Input!" << endl << endl;
	}
}

string Users::RemoveMyGood()
{
	string Id="";
	cout << "������Ҫ�¼ܵ���ƷID: ";
	cin >> Id;
	Goods* allgood = Goods::GetInstance();
	if (allgood->CheckGoodId(Id))
	{
		cout << "ȷ��Ҫ�¼ܸ���Ʒ��?" << endl;
		allgood->PrintGoods("Seller", "Last","", Id);
		cout << "��ѡ��(y/n): ";
		string in = "";
		cin >> in;
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

string Users::CheckMyOrder()
{
	return " SELECT * FROM order";
}




//��ҹ���  BUYER



void Users::UserBuyer()
{
	while (true)
	{
		cout << "===========================================================================================" << endl
			<< "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������" << endl
			<< "===========================================================================================" << endl << endl;
		cout << "����������� ";
		string in = "";
		cin >> in;
		try
		{
			if (in.length() > 1)
			{
				throw 1;
			}
			if (in[0] < '1' || in[0]>'6') throw 1;
			switch ((int)(in[0] - 48))
			{
			case 1:
				_CurrUser->SPAnaSQL(CheckGood());
				break;
			case 2:
				_CurrUser->SPAnaSQL(BuyGood());
				break;
			case 3:
				break;
				_CurrUser->SPAnaSQL(SearchGood());
				break;
			case 4:
				_CurrUser->SPAnaSQL(CheckOrder());
				break;
			case 5:
				_CurrUser->SPAnaSQL(CheckGoodAccura());
				break;
			case 6:
				return;
			}
		}
		catch (int)
		{
			cout << "Invalid Input!" << endl << endl;
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
	string Id = "", Stock = "";
	cout << "��������Ʒ ID�� "; cin >> Id;
	Goods* allgood = Goods::GetInstance();
	if (!allgood->CheckGoodId(Id))
	{
		cout << "��ƷID�����ڣ�" << endl << endl;
		return"";
	}
	cin >> Stock;
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
	string _UpTime ="";
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	_UpTime = to_string(timeinfo->tm_year + 1900) + "-";
	if (timeinfo->tm_mon < 10) _UpTime += "0";
	_UpTime += (to_string(timeinfo->tm_mon+1) + "-");
	if (timeinfo->tm_mday < 10) _UpTime += "0";
	_UpTime += to_string(timeinfo->tm_mday);
	Orders* allorder = Orders::GetInstance();
	string OrderId = "T" + to_string(allorder->GetAll());
	return "INSERT INTO order VALUES ( " + OrderId + "," + Id + "," + allgood->GetPrice(Id)
		+ "," + Stock + "," + _UpTime + "," + allgood->GetSellerID(Id) + ","
		+ _CurrUser->GetUserId() + " )";
}

string Users::SearchGood()
{
	string Name;
	cout << "��������Ʒ����: ";
	cin >> Name;
	return "SELECT * FROM commodity WHERE commodityName  CONTAINS "+Name;
}
string Users::CheckOrder()
{
	return "SELECT * FROM order";
}
string Users::CheckGoodAccura()
{
	cout << "����������Ҫ�鿴����ƷID: ";
	string Id="";
	cin >> Id;
	return "SELECT * FROM commodity WHERE commodityID CONTAINS "+Id;
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
		cin >> in;
		try
		{
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
	}
}

void Users::ChangeMe()
{
	string in;
	cout << "��ѡ���޸ĵ����� ��1.�û��� 2.��ϵ��ʽ 3.��ַ����";
	cin >> in;
	try
	{
		if (in.length() > 1)
		{
			throw 1;
		}
		if (in[0] < '1' || in[0]>'3') throw 1;
		string aka = "";
		switch ((int)(in[0] - 48))
		{
		case 1:
			while (true)
			{
				try
				{
					cout << "�������޸ĺ���û����� " << endl;
					cin >> aka;
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

			}
			break;
		case 2:
			cout << "�������޸ĺ����ϵ��ʽ�� ";
			cin >> aka;
			_CurrUser->ChangePhone(aka);
			ResetDocuUser();
			cout << "�޸ĳɹ���" << endl << endl;
			break;
		case 3:
			cout << "�������޸ĺ�ĵ�ַ�� ";
			cin >> aka;
			_CurrUser->ChangeAddress(aka);
			ResetDocuUser();
			cout << "�޸ĳɹ���" << endl << endl;
			break;
		case 4:
			return;
		}
	}
	catch (int)
	{
		cout << "Invalid Input!" << endl << endl;
	}
	return;
}

void Users::AddMoney()
{
	cout << "�������ֵ�� ";
	string Price= "";
	cin >> Price;
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
	_CurrUser->AddMoney(stod(Price));
	ofstream out_file;
	out_file.open("E:\\Project 1\\Project 1\\recharge.txt", ios::app);
	out_file << _CurrUser->GetUserId() << " " << Price<<" " << endl;
	cout << "��ֵ�ɹ�����ǰ�� " << _CurrUser->GetMoney() << endl;
	ResetDocuUser();
	return;
}
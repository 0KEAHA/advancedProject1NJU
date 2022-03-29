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
		cout << "请输入管理员姓名: "; 
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		cout << "请输入密码: ";
		getline(cin, password);
		if (password.find(" ") != string::npos) throw 1.0;
		cout << endl;
		if (Id == m_id && password == m_password)
		{
			cout << endl
				<< "    -----登录成功!------" << endl
				<< endl;
			AfterLogin();
		}
		else
		{
			cout << endl
				<< "----账号或密码错误,登陆失败----" << endl
				<< endl;
			return;
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
	}
}

void Admin::AfterLogin()
{
	while (true) {
		cout << "==========================================================================" << endl
			<< "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl
			<< "==========================================================================" << endl
			<< endl
			<< "请输入操作: ";
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
			cout << "输入无效! 请重新正确输入!" << endl;
		}
		catch (double)
		{
			cout << "请不要输入空格！" << endl << endl;
		}
	}
	return;
}




//生成SQL指令



string Admin::CheckGoods()
{
	return "SELECT * FROM commodity";
}

string Admin::SearchGoods()
{
	try
	{
		cout << "请输入商品名称: ";
		string in = "";
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		return "SELECT * FROM commodity WHERE commodityName CONTAINS " + in;
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
	}
	return"";
}

string Admin::DisableGood()
{
	try
	{
		cout << "请输入要下架的商品ID: ";
		string in = "";
		getline(cin, in);
		if (in.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (allgood->CheckGoodId(in))
		{
			if (allgood->CheckAvailable(in))
			{
				cout << "确认要下架该商品吗?" << endl;
				allgood->PrintGoods("Admin", "Last", "", in);
				cout << "请选择(y/n):";
				string in2 = "";
				getline(cin, in2);
				if (in2.find(" ") != string::npos) throw 1.0;
				try
				{
					if (in2 == "y")
					{
						cout << "下架成功！" << endl << endl;
						return "UPDATE commodity SET state = removed WHERE commodityID CONTAINS " + in;
					}
					if (in2 == "n")
					{
						cout << "取消下架" << endl << endl;
						return "";
					}
					else
						throw 1;
				}
				catch (int)
				{
					cout << "输入不合法,下架取消!" << endl << endl;
					return "";
				}
			}
			else
			{
				cout << "该商品已为下架状态！" << endl << endl;
				return "";
			}
		}
		else
		{
			cout << "商品ID不存在,下架失败" << endl;
			return "";
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
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
	cout << "请输入要封禁的用户ID: ";
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
				cout << "用户已被封禁" << endl << endl;
				return "";
			}
			cout << "确认要封禁该用户吗?" << endl;
			cout << "*************************************************************************" << endl
				<< "用户ID\t\t用户名\t\t联系方式\t\t\t地址\t\t\t钱包余额" << endl;
			alluser->PrintUser("AdminDisable", in);
			cout << "*************************************************************************" << endl;
			cout << "请选择(y/n): ";
			string in2 = "";
			getline(cin, in2);
			if (in2.find(" ") != string::npos) throw 1.0;
			try
			{
				if (in2 == "y")
				{
					cout << "封禁成功！" << endl << endl;
					return "UPDATE user SET state = inactive WHERE sellerID CONTAINS " + in;
				}
				if (in2 == "n")
				{
					cout << "取消封禁" << endl << endl;
					return "";
				}
				else
					throw 1;
			}
			catch (int)
			{
				cout << "输入不合法,封禁取消!" << endl << endl;
				return "";
			}
		}
		else
		{
			cout << "用户ID不存在,封禁失败" << endl << endl;
			return "";
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
		return"";
	}
}



//执行函数



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
//小型函数
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
		cout << "正常" << endl;
		return;
	}
	if (_UserState == "inactive")
	{
		cout << "封禁" << endl;
		return;
	}
}
void User::PrintUserSelf()
{
	cout << "***************************" << endl
		<< "用户名： " << _UserName << endl
		<< "联系方式： " << _PhoneNumber << endl
		<< "地址： " << _Address << endl
		<< "钱包余额： " <<GetMoney() << endl
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



//文件操作

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




// 小函数




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
		cout << "请输入用户名： ";
		getline(cin, UserId);
		if (UserId.find(" ") != string::npos|| UserId.find(",") != string::npos) throw 1.0;
		if (UserId.length() > 10) 
		{
			cout << "用户名过长！请小于十一个字母！" << endl << endl; return;}
		for (string::iterator it = UserId.begin(); it != UserId.end(); it++)
		{
			if (*it < 'A' || *it>'z' || (*it > 'Z' && *it < 'a')) {
				cout << "----请输入英文字母！已退出注册----" << endl << endl;
				return;
			}
		}
		cout << "请输入密码： "; 
		getline(cin, Pass);
		for (string::iterator it = Pass.begin(); it != Pass.end(); it++)
		{
			if ((*it < 'a' && (*it < '0' || *it>'9')) || *it > 'z')
			{
				cout << "----请输入小写字母或数字！已退出注册----" << endl << endl;
				return;
			}
		}
		if (Pass.find(" ") != string::npos|| Pass.find(",") != string::npos) throw 1.0;
		if (CheckUserName(UserId))
		{
			cout << "----用户名已存在，退出注册----" << endl << endl;
			return;
		}
		else
		{
			string newPass;
			newPass.clear();
			cout << "请再次确认密码：";
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
				cout << "-----注册成功,若继续操作请登录----" << endl << endl;
			}
			else
			{
				cout << "两次密码不一致，已退出注册！" << endl << endl;
			}
			return;
		}
	}
	catch (double)
	{
		cout << "请不要输入空格或者逗号！" << endl << endl;
		return;
	}
}

void Users::UserLogin()
{
	try
	{
		string UserId = "";
		string Pass = "";
		cout << "请输入用户名： ";
		getline(cin, UserId);
		if (UserId.find(" ") != string::npos) { throw 1.0; }
		cout << "请输入密码： "; 
		getline(cin, Pass);
		if (Pass.find(" ") != string::npos) { throw 1.0; }
		if (!CheckUserName(UserId))
		{
			cout << "----用户不存在！----" << endl << endl;
			_CurrUser = nullptr;
			return;
		}
		else
		{
			_CurrUser = &AllUsers[GetUserId(UserId)];
			if (_CurrUser->GetUserState() == "inactive")
			{
				cout << "您已被封禁！" << endl << endl;
				return;
			}
			if (_CurrUser->CheckPass(Pass))
			{
				cout << "----登录成功！----" << endl << endl;
				Carts* AllCart = Carts::GetInstance();
				AllCart->SetUserId(GetUserId(UserId));
				AfterLogin();
				return;
			}
			else
			{
				cout << "----密码错误！请重新登录！----" << endl << endl;
				return;
			}
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
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
		cout << "用户ID\t用户名\t联系方式\t\t地址\t\t钱包余额\t用户状态" << endl;
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
			<< "1.我是买家  2.我是卖家  3.个人信息管理 4.注销登录" << endl
			<< "=================================================" << endl << endl;
		string in = "";
		cout << "请输入操作： ";
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
			cout << "请不要输入空格！" << endl << endl;
			break;
		}
	}
}




//卖家操作


void Users::UserSeller()
{
	while (true)
	{
		cout << "===========================================================================" << endl
			<< "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl
			<< "===========================================================================" << endl << endl;
		string in = "";
		cout << "请输入操作： "; 
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
			cout << "请不要输入空格！" << endl << endl;
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
		cout << "请输入商品名称： ";
		getline(cin, GoodName);
		if (GoodName.find(" ") != string::npos|| GoodName.find(",") != string::npos) throw 1.0;
		for (string::iterator it = GoodName.begin(); it != GoodName.end(); it++)
		{
			if (*it < 'A' || *it>'z' || (*it > 'Z' && *it < 'a'))
			{
				cout << "----请输入英文字母！已退出发布----" << endl << endl;
				return"";
			}
		}
		cout << "请输入商品价格： ";
		getline(cin, Price);
		if (Price.find(" ") != string::npos) throw 1.0;
		cout << "请输入商品数量： ";
		getline(cin, Stock);
		if (Stock.find(" ") != string::npos|| Stock.find(",") != string::npos) throw 1.0;
		cout << "请输入商品描述： "; 
		getline(cin, Descrip);
		string::iterator it;
		it = Price.begin();
		if (GoodName.length() > 20)
		{
			cout << "---输入名称过长，请少于21个字符---" << endl << endl;
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
			cout << "---价格格式不正确，已退出发布，正确发布请输入一位小数或整数---" << endl << endl;
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
			cout << "---数量格式不正确，请输入正整数---" << endl << endl;
			return "";
		}
		if (Descrip.length() > 200)
		{
			cout << "----输入描述过长,已退出发布----" << endl << endl;
			return "";
		}
		if (Descrip.find(",") != string::npos)
		{
			cout << "----描述不允许输入 \",\" 已退出发布----" << endl << endl;
			return"";
		}
		cout << "上架成功！" << endl << endl;
		return "INSERT INTO commodity VALUES ( " + GoodName + " " + Price + " "
			+ Stock + " " + Descrip + " )";
	}
	catch (double)
	{
		cout << "请不要输入空格或者逗号！" << endl << endl;
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
		cout << "请输入被修改的商品的ID： ";
		getline(cin, GoodId);
		if (GoodId.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (!allgood->CheckGoodId(GoodId))
		{
			cout << "商品ID不存在!" << endl << endl;
			return "";
		}
		cout << "请输入被修改的商品的属性 （1.价格 2.描述 3.库存 4.取消): ";
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
					cout << "请输入被修改商品的价格: ";
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
						cout << "---价格格式不正确，已退出修改，正确修改请输入一位小数或整数---" << endl << endl;
						return "";
					}
					cout << "请确认被修改的商品信息无误!" << endl;

					all->PrintWhenChange(GoodId, "Price", Price);
					cout << "确认修改? (y/n)";
					in.clear();
					getline(cin, in);
					if (in.find(" ") != string::npos) throw 1.0;
					if (in == "y")
					{
						return ("UPDATE commodity SET price = " + Price + " WHERE commodityID CONTAINS " + GoodId);
					}
					if (in == "n")
					{
						cout << "取消修改!" << endl << endl;
						return"";
					}
					else
					{
						cout << "Invalid Input" << endl << endl;
						return "";
					}
				case 2:
					cout << "请输入被修改商品的描述: ";
					getline(cin, Descrip);
					if (Descrip.length() > 200)
					{
						cout << "----输入描述过长,已退出修改----" << endl << endl;
						return "";
					}
					if (Descrip.find(",") != string::npos)
					{
						cout << "----不允许输入 \",\" 已退出修改----" << endl << endl;
						return"";
					}
					else
					{
						cout << "请确认被修改的商品信息无误!" << endl;

						all->PrintWhenChange(GoodId, "Descrip", Descrip);
						cout << "确认修改? (y/n)";
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
					cout << "请输入修改后商品数量：";
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
					cout << "修改成功！" << endl << endl;
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
			cout << "请不要输入空格！" << endl << endl;
			return"";
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
		return"";
	}
	return "";
}

string Users::RemoveMyGood()
{
	try
	{
		string Id = "";
		cout << "请输入要下架的商品ID: ";
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (_CurrUser->CheckMyGoodId(Id))
		{
			cout << "确认要下架该商品吗?" << endl;
			allgood->PrintGoods("Seller", "Last", "", Id);
			cout << "请选择(y/n): ";
			string in = "";
			getline(cin, in);
			if (in.find(" ") != string::npos) throw 1.0;
			if (in == "y")
			{
				return "UPDATE commodity SET state = removed WHERE commodityID CONTAINS " + Id;
			}
			if (in == "n")
			{
				cout << "取消下架" << endl << endl;
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
		cout << "请不要输入空格！" << endl << endl;
		return"";
	}
	return"";
}

string Users::CheckMyOrder()
{
	return "SELECT * FROM order";
}




//买家功能  BUYER



void Users::UserBuyer()
{
	Carts* AllCart = Carts::GetInstance();
	while (true)
	{
			cout << "=========================================================================================================" << endl
				<< "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.管理购物车 7.返回用户主界面" << endl
				<< "=========================================================================================================" << endl << endl;
			cout << "请输入操作： ";
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
			cout << "请不要输入空格！" << endl << endl;
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
		cout << "请输入商品 ID： ";
		getline(cin, Id);
		if (Id.find(" ") != string::npos) throw 1.0;
		Goods* allgood = Goods::GetInstance();
		if (!allgood->CheckGoodId(Id))
		{
			cout << "商品ID不存在！" << endl << endl;
			return"";
		}
		cout << "请输入购买数量：";
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
			cout << "---数量格式不正确，请输入正整数---" << endl << endl;
			return "";
		}
		int integer = stoi(Stock);
		if (integer > allgood->GetGoodStock(Id))
		{
			cout << "商品库存不足！" << endl << endl;
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
		cout << "请不要输入空格！" << endl << endl;
		return"";
	}
}

string Users::SearchGood()
{
	try
	{
		string Name;
		cout << "请输入商品名称: ";
		getline(cin, Name);
		if (Name.find(" ") != string::npos) throw 1.0;
		return "SELECT * FROM commodity WHERE commodityName  CONTAINS " + Name;
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl;
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
		cout << "请输入您想要查看的商品ID: ";
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
			cout << "商品ID不存在！" << endl;
			return"";
		}
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl;
		return"";
	}
}

void Users::Me()
{
	while (true)
	{
		cout << "=================================================" << endl
			<< "1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl
			<< "=================================================" << endl << endl;
		cout << "请输入操作： ";
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
			cout << "请不要输入空格！" << endl << endl;
		}
	}
}

void Users::ChangeMe()
{
	string in;
	cout << "请选择修改的属性 （1.用户名 2.联系方式 3.地址 4.密码 5.退出）：";
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
					cout << "请输入修改后的用户名： ";
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
					cout << "修改成功！" << endl << endl;
					break;
				}
				catch (int)
				{
					cout << "用户名已存在，请重新输入" << endl;
				}
				catch (double)
				{
					cout << "请不要输入空格或者逗号！" << endl << endl;
				}

			}
			break;
		case 2:
			cout << "请输入修改后的联系方式： ";
			try {
				getline(cin, aka);
				if (aka.find(" ") != string::npos || aka.find(",") != string::npos)
				{
					throw 1;
				}
				_CurrUser->ChangePhone(aka);
				ResetDocuUser();
				cout << "修改成功！" << endl << endl;
				break;
			}
			catch (int)
			{
				cout << "请不要输入空格或者逗号！" << endl << endl;
			}
			break;
		case 3:
			cout << "请输入修改后的地址： ";
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
						cout << "----请输入英文字母！已退出注册----" << endl << endl;
						return;
					}
				}
				_CurrUser->ChangeAddress(aka);
				ResetDocuUser();
				cout << "修改成功！" << endl << endl;
				break;
			}
			catch (int)
			{
				cout << "请不要输入空格或者逗号！" << endl << endl;
			}
			break;
		case 4:
			cout << "请输入原密码： ";
			getline(cin, pa);
			if (_CurrUser->CheckPass(pa))
			{
				while (true)
				{
					cout << "请输入新密码：";
					pa.clear();
					getline(cin, pa);
					if (_CurrUser->CheckPass(pa))
					{
						cout << "新密码不得与原密码相同！" << endl;
						continue;
					}
					else
					{
						string newpa;
						cout << "请再次输入新密码：" << endl;
						getline(cin, newpa);
						if (newpa == pa)
						{
							_CurrUser->ChangePass(pa);
							ResetDocuUser();
							cout << "修改成功！" << endl << endl;
							break;
						}
						else
						{
							cout << "两次密码不一致，请重新修改" << endl << endl;
							continue;
						}
					}
				}
			}
			else
			{
				cout << "密码输入错误，已退出修改" << endl << endl;
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
		cout << "请不要输入空格！" << endl << endl;
	}
	return;
}

void Users::AddMoney()
{
	cout << "请输入充值金额： ";
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
		cout << "---金额不正确，充值失败，请输入一位小数或整数---" << endl << endl;
		return ;
	}
	catch (double)
	{
		cout << "请不要输入空格！" << endl << endl;
	}
	_CurrUser->AddMoney(stod(Price));
	ofstream out_file;
	out_file.open("recharge.txt", ios::app);
	out_file << _CurrUser->GetUserId() << " " << Price<<" " << endl;
	cout << "充值成功，当前余额： " << _CurrUser->GetMoney() << endl;
	ResetDocuUser();
	return;
}
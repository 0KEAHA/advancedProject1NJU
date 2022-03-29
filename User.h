#define CUser

#ifndef HGen
#define HGen
#include "General.h"
#endif
#ifndef HCla
#define HCla
#include "ClassGen.h"
#endif

class Admin
{
private:
	const string m_id;
	const string m_password;
	Admin() : m_id("admin"), m_password("123456") {};
	static Admin* P_Admin;
public:
	static Admin* GetInstance();
	void DeleteInstance();
	
	void Admin_login();
	
	void AfterLogin();
	
	string CheckGoods();
	string SearchGoods();
	string DisableGood();
	string CheckDeals();
	string CheckUsers();
	string DisableUser();
	
	void AnaSQL(string);//注意封禁用户副作用

	void _CheckGoods();
	void _SearchGoods(string);
	void _DisableGood(string);
	void _CheckDeals();
	void _CheckUsers();
	void _DisableUser(string);
};



class User
{
private:
	string _UserId;
	string _UserName;
	string _Password;
	string _PhoneNumber;
	string _Address;
	string _UserState;
	double _Money;
public:
	User();
	//注册
	User(string Id, string name, string password);
	//文件生成用户
	User(string Id, string name, string password, string phone, string address, string balance, string state);
	
	User& operator=(const User&);
	string GetUserName();
	string GetUserId();
	string GetUserState();
	string OutInfo();
	void DisableUser();
	bool CheckPass(string);
	void PrintUserAdmin();
	void PrintUserDisable();
	void PrintUserSelf();

	//Seller
	bool CheckMyGoodId(string Id);
	void AddGood(string,double,int ,string);
	void CheckMyGood();
	void ChangeMyGoodPrice(string,double);
	void ChangeMyGoodDescrip(string,string);
	void RemoveMyGood(string);
	void CheckMyOrder();

	//Buyer
	void CheckGood();
	string GetMoney();//计算器
	void ChangeName(string);
	void ChangePhone(string);
	void ChangePass(string);
	void ChangeAddress(string);
	void AddMoney(double);
	void BuyGood(string,string,string,string,string,string);//缺省买家ID
	void SearchGood(string);
	void CheckOrder();
	void CheckGoodAccura(string);
	
	void AnaSQL(string);
	void SPAnaSQL(string);
};

class Users
{
private:
	static Users* P_AllUsers;
	User* _CurrUser;
	map<string, User> AllUsers;
	Users() { _CurrUser = nullptr; };
public:
	static Users* GetInstance();
	void DeleteInstance();

	string GetUserState(string Id);
	int GetAll();
	void InputDocuUser();
	void ResetDocuUser();

	User* GetPUser();
	void AddUser();
	void UserLogin();
	void AfterLogin();
	bool CheckUserName(string);
	bool CheckUserId(string);
	string GetUserId(string Name);
	//三种 Admin AdminDisable UserSelf
	void PrintUser(string commander, string Id = "");
	void DisaleUser(string Id);




	void UserSeller();//六个功能
	string AddGood();
	string CheckMyGood();
	string ChangeMyGood();
	string RemoveMyGood();
	string CheckMyOrder();

	void UserBuyer();//七个功能
	
	string CheckGood();
	string BuyGood();
	string SearchGood();
	string CheckOrder();
	string CheckGoodAccura();
	
	void Me();
	void ChangeMe();
	void AddMoney();
};


void UpCommand(string);//写入命令文件
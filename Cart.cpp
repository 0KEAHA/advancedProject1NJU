#include "Cart.h"


//Cart

Cart::Cart()
{
	_UserId = "";
	_UnitCommdity.clear();
}
Cart::Cart(string UserId)
{
	_UserId = UserId;
	_UnitCommdity.clear();
}
Cart::Cart(const Cart& C)
{
	if (this != &C)
	{
		_UserId = C._UserId;
		_UnitCommdity = C._UnitCommdity;
	}
}
Cart::Cart(string UserId, vector<pair<string,int> > UnitCommodity)
{
	_UserId = UserId;
	_UnitCommdity = UnitCommodity;
}

Cart& Cart::operator=(const Cart& C)
{
	if (this != &C)
	{
		_UserId = C._UserId;
		_UnitCommdity = C._UnitCommdity;
	}
	return *this;
}

void Cart::AddCart(string Id,int num)
{
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		if (it->first == Id)
		{
			it->second += num;
			cout << "添加成功！\n" << endl;
			return;
		}
	}
	pair<string, int>p(Id, num);
	_UnitCommdity.push_back(p);
	cout << "添加成功！\n" << endl;
	return;
}
void Cart::BuyAll()
{
	Users* AllUser = Users::GetInstance();
	Goods* AllGood = Goods::GetInstance();
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		cout << "商品" << it->first <<"购买中……" << endl;
		if (AllGood->CheckAvailable(it->first) && AllGood->GetGoodStock(it->first)>=it->second)
		{
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
			if ((AllUser->GetPUser())
				->SPAnaSQL(
					"INSERT INTO order VALUES ( " + OrderId + "," + it->first + "," + AllGood->GetPrice(it->first)
					+ "," + to_string(it->second) + "," + _UpTime + "," + AllGood->GetSellerID(it->first) + ","
					+ _UserId + " )"))
			{
				cout << "商品" << it->first << "购买成功！" << endl;
				DeletSome(it->first);
				cout << "商品" << it->first << "已从购物车中移除！" << endl;
			}
			else
			{
				cout << "余额不足！商品" << it->first << "购买失败！" << endl;
			};
			continue;
		}
		else
		{
			cout << "商品" << it->first << "已下架或库存不足!" << endl;
		}
	}
	cout << "除失效商品、库存不足商品、余额不足外，全部商品已购买!" << endl << endl;
	return;
}
void Cart::ClearDis()
{
	Goods* AllGood = Goods::GetInstance();
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		if (!AllGood->CheckAvailable(it->first))
		{
			_UnitCommdity.erase(it);
		}
	}
	cout << "失效商品已全部清除！" << endl << endl;
	return;
}
void Cart::Erase()
{
	_UnitCommdity.clear();
	cout << "商品已全部清除！" << endl;
	return;
}
void Cart::DeletSome(string Id)
{
	Goods* AllGood = Goods::GetInstance();
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		if (it->first == Id)
		{
			_UnitCommdity.erase(it);
			break;
		}
	}
	return;
}
void Cart::ShowAll()
{
	Goods* AllGood = Goods::GetInstance();
	cout << "商品ID\t商品名称\t价格\t上架时间\t卖家ID\t意愿数量" << endl;
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		AllGood->PrintCart(it->first); cout << it->second << endl;;
	}
	cout << endl;
	return;
}
bool Cart::CheckId(string Id)
{
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		if (it->first == Id)
		{
			return true;
		}
	}
	return false;
}
string Cart::Outinfo()
{
	string ans = "";
	ans += _UserId+=",";
	for (auto it = _UnitCommdity.begin(); it != _UnitCommdity.end(); it++)
	{
		ans+= (it->first+","+to_string(it->second)+",");
	}
	ans.pop_back();
	return ans;
}


// All Carts
Carts* Carts::P_AllCarts = nullptr;
void Carts::SetUserId(string Id)
{
	_CurrUserId = Id;
}
Carts* Carts::GetInstance()
{
	if (P_AllCarts == nullptr)
	{
		P_AllCarts = new Carts;
	}
	return P_AllCarts;
}
void Carts::DeleteInstance()
{
	if (P_AllCarts != nullptr)
	{
		delete P_AllCarts;
		P_AllCarts = nullptr;
	}
	return;
}

void Carts::InputDocuCarts()
{
	ifstream in_file;
	in_file.open("cart.txt",
		ios::in);
	if (!in_file)
	{
		ofstream out_file;
		out_file.open("cart.txt",
			ios::out);
		out_file.close();
		return;
	}
	AllCarts.clear();
	vector<string> Unit;
	string tmp = "";
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
		vector<pair<string, int> > vp;
		for (int i = 1; i < Unit.size()-1; ++++i)
		{
			pair<string, int> p(Unit[i], stoi(Unit[i + 1]));
			vp.push_back(p);
		}
		AllCarts[Unit[0]]=Cart(Unit[0],vp);
		Unit.clear();
		vp.clear();
	}
	if (in_file.eof())
	{
		in_file.close();
	}
	else
	{
		cout << "Read Cart txt Wrong!" << endl;
	}
}
void Carts::ResetDocucarts()
{
	ofstream out_file;
	out_file.open("cart.txt", ios::out);
	if (out_file.fail())
	{
		cout << "Open cart.txt to write Error!" << endl;
		exit(-1);
	}
	if (AllCarts.empty() != true)
	{
		auto mmm = AllCarts.end(); mmm--;
		auto it = AllCarts.begin();
		while(it != mmm)
		{
			out_file << it->second.Outinfo()<<endl;
			it++;
		}
		out_file << it->second.Outinfo();
	}
	out_file.close();
	InputDocuCarts();
	return;
}

void Carts::GovCarts()
{
	while (true)
	{
		cout << "============================================================================" << endl
			<< "1.查看购物车 2.添加商品 3.清空失效商品 4.删除商品 5.清空全部商品 6.购买全部商品 7.退出" << endl
			<< "============================================================================" << endl << endl;
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
			if (in[0] < '1' || in[0]>'7')
			{
				throw 1;
			}
			else
			{
				switch ((int)(in[0] - 48))
				{
				case 1:
					ShowAll();
					break;
				case 2:
					AddCart();
					break;
				case 3:
					ClearDis();
					break;
				case 4:
					DeletSome();
					break;
				case 5:
					Erase();
					break;
				case 6:
					BuyAll();
					break;
				case 7:
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
}

void Carts::ShowAll()
{
	AllCarts[_CurrUserId].ShowAll();
	return;
}
void Carts::AddCart()
{
	Goods* AllGood = Goods::GetInstance();
	try
	{
		string Id; string num;
		cout << "请输入加购商品Id： ";
		getline(cin, Id);
		if (Id.find(" ") != string::npos || Id.find(",") != string::npos)
		{
			throw 1.0;
		}
		if (!AllGood->CheckGoodId(Id)||!AllGood->CheckAvailable(Id))
		{
			cout << "商品不存在或已下架!" << endl << endl;
			return;
		}
		cout << "请输入加购数量： ";
		getline(cin, num);
		if (num[0] < '1' || num[0]>'9')throw 1;
		for (int i = 1; i < num.size(); i++)
		{
			if (num[i] < '0' || num[i]>'9')throw 1;
		}
		AllCarts[_CurrUserId]=Cart(_CurrUserId);
		AllCarts[_CurrUserId].AddCart(Id, stoi(num));
		ResetDocucarts();
		return;
	}
	catch (double)
	{
		cout << "请不要输入空格!" << endl << endl;;
		return;
	}
	catch (int)
	{
		cout << "Invalid Input!" << endl << endl;
		return;
	}
	return;
}

void Carts::Erase()
{
	cout << "确认要清空购物车吗?[y/n]:";
	string in = "";
	getline(cin, in);
;	if (in == "y")
	{
		AllCarts[_CurrUserId].Erase();
		ResetDocucarts();
	}
	else if (in == "n")
	{
		cout << "已取消操作" << endl << endl;
		return;
	}
	else
	{
		cout << "输入不合法,操作已取消" << endl << endl;
	}
	return;
}
void Carts::BuyAll()
{
	cout << "确认要购买购物车全部商品吗?[y/n]:";
	string in = "";
	getline(cin, in);
	if (in == "y")
	{
		AllCarts[_CurrUserId].BuyAll();
		ResetDocucarts();
		return;
	}
	else if (in == "n")
	{
		cout << "已取消操作" << endl << endl;
		return;
	}
	else
	{
		cout << "输入不合法,操作已取消" << endl << endl;
	}
	return;
}
void Carts::ClearDis()
{
	cout << "确认要清空购物车全部失效商品吗?[y/n]: ";
	string in = "";
	getline(cin, in);
	if (in == "y")
	{
		AllCarts[_CurrUserId].ClearDis();
		ResetDocucarts();
		return;
	}
	else if (in == "n")
	{
		cout << "已取消操作" << endl << endl;
		return;
	}
	else
	{
		cout << "输入不合法,操作已取消" << endl << endl;
	}
	return;
}

void Carts::DeletSome()
{
	string Id = "";
	cout << "请输入商品Id: ";
	getline(cin, Id);
	if (AllCarts[_CurrUserId].CheckId(Id))
	{
		cout << "确认要删除此商品吗?[y/n]:";
		string in = "";
		getline(cin, in);
		if (in == "y")
		{
			AllCarts[_CurrUserId].DeletSome(Id);
			ResetDocucarts();
			return;
		}
		else if (in == "n")
		{
			cout << "已取消操作" << endl << endl;
			return;
		}
		else
		{
			cout << "输入不合法,操作已取消" << endl << endl;
		}
		return;
	}
	else
	{
		cout << "购物车中不存在此商品" << endl << endl;
	}
	return;
}
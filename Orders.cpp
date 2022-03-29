#include "Orders.h"

//Order Method

Order::Order()
{
	_OrderId = "";
	_GoodId = "";
	_Num = "0";
	_Date = "";
	_Price = "0.0";
	_SellerId = "";
	_BuyerId = "";
}
Order::Order(string Id,string GoodId, double Price,
	int Num, string SellerId, string BuyerId)
{
	_OrderId = Id;
	_GoodId = GoodId;
	Price = round(Price * 10) / 10.0;
	_Price = to_string(Price);
	_Price.erase(_Price.end() - 4, _Price.end());
	_Price.pop_back();
	_Num = to_string(Num);
	_SellerId = SellerId;
	_BuyerId = BuyerId;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	_Date = to_string(timeinfo->tm_year + 1900) + "-";
	if (timeinfo->tm_mon < 10) _Date += "0";
	_Date += (to_string(timeinfo->tm_mon+1) + "-");
	if (timeinfo->tm_mday < 10) _Date += "0";
	_Date += to_string(timeinfo->tm_mday);
}
Order::Order(string OrderId, string GoodId, string Price,
	string Num, string Date,string SellerId, string BuyerId)
{
	_OrderId = OrderId;
	_GoodId = GoodId;
	_Price = Price;
	_Num = Num;
	_Date = Date;
	_SellerId = SellerId;
	_BuyerId = BuyerId;
}
Order::Order(const Order& d)
{
	_OrderId = d._OrderId;
	_GoodId = d._GoodId;
	_Price = d._Price;
	_Num = d._Num;
	_Date = d._Date;
	_SellerId = d._SellerId;
	_BuyerId = d._BuyerId;
}

Order& Order::operator=(const Order& d)
{
	if (this != &d)
	{
		_OrderId = d._OrderId;
		_GoodId = d._GoodId;
		_Price = d._Price;
		_Num = d._Num;
		_Date = d._Date;
		_SellerId = d._SellerId;
		_BuyerId = d._BuyerId;
	}
	return *this;
}


//打印信息
void Order::PrintAdmin()
{
	cout << _OrderId << "\t" << _GoodId << "\t" << _Price << "   "
		<< _Num << "   " << _Date << "  " << _SellerId << "\t"
		<< _BuyerId << endl;
	return;
}
void Order::PrintSeller()
{
	cout << _OrderId << "\t" << _GoodId << "\t" << _Price << "   "
		<< _Num << "   " << _Date << "  "
		<< _BuyerId << endl;
	return;
}
void Order::PrintBuyer()
{
	cout << _OrderId << "\t" << _GoodId << "\t" << _Price << "   "
		<< _Num << "   " << _Date << "  " 
		<< _SellerId <<endl;
	return;
}

//小函数
string Order::GetBuyerId()
{
	return  _BuyerId;
}
string Order::GetSellerId()
{
	return _SellerId;
}
string Order::OutInfo()
{
	return _OrderId + "," + _GoodId + "," + _Price + ","
		+ _Num + "," + _Date + "," + _SellerId + "," + _BuyerId;
}



//Orders Method

Orders* Orders::P_GenOrders = nullptr;
Orders* Orders::GetInstance()
{
	if (P_GenOrders == nullptr)
	{
		P_GenOrders = new Orders;
	}
	return P_GenOrders;
}
void Orders::DeleteInstance()
{
	if (P_GenOrders)
	{
		delete P_GenOrders;
		P_GenOrders = nullptr;
	}
	return;
}

//文件操作
void Orders::InputDocuOrder()
{
	ifstream in_file;
	in_file.open("order.txt",
		ios::in);
	if (!in_file)
	{
		ofstream out_file;
		out_file.open("order.txt",
			ios::out);
		out_file.close();
		return;
	}
	AllOrders.clear();
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
		AllOrders[Unit[0]] = Order(Unit[0], Unit[1], Unit[2], Unit[3], Unit[4], Unit[5], Unit[6]);
		Unit.clear();
	}
	if (in_file.eof())
	{
		in_file.close();
	}
	else
	{
		cout << "Read Order txt Wrong!" << endl;
		in_file.close();
	}
}

void Orders::ResetDocuOrder()
{
	ofstream out_file;
	out_file.open("order.txt",
		ios::out);
	if (out_file.fail())
	{
		cout << "Open order.txt to write Error!" << endl;
		exit(-1);
	}
	out_file << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
	if (AllOrders.empty() != true)
	{
		out_file << endl;
		map<string, Order>::iterator it = AllOrders.begin();
		auto mmm = AllOrders.end();
		--mmm;
		while (it != mmm)
		{
			out_file << it->second.OutInfo() << endl;
			it++;
		}
		out_file << it->second.OutInfo();
	}
	out_file.close();
	InputDocuOrder();
	return;
}

void Orders::UpOrder(string OrderId,string GoodId,string Price, string Num, string Date,string SellerId, string BuyerId)
{
	AllOrders[OrderId] = Order(OrderId, GoodId, Price, Num,Date, SellerId, BuyerId);
	ResetDocuOrder();
	return;
}


//小函数
int Orders::GetAll()
{
	int num = 1;
	for (map<string, Order>::iterator it = AllOrders.begin();it!=AllOrders.end();it++)
	{
		num++;
	}
	return num;
}

void Orders::PrintOrders(string commander, string SellerId, string BuyerId)
{
	cout << "****************************************************************" << endl;
	map<string, Order>::iterator it = AllOrders.begin();
	if (commander == "Admin")
	{
		cout << "orderID  " << "commodityID  " << "unitPrice "
				<< "number   " << "date\t" << "sellerID  " << "buyerID" << endl;
		if (AllOrders.empty() != true)
		{
			while (it != AllOrders.end())
			{
				it->second.PrintAdmin();
				it++;
			}
		}
	}
	else if (commander == "Seller")
	{
		cout << "orderID  " << "commodityID  " << "unitPrice "
			<< "number   " << "date\t" << "buyerID" << endl;
		if (AllOrders.empty() != true)
		{
			while (it != AllOrders.end())
			{
				if (it->second.GetSellerId() == SellerId)
				{
					it->second.PrintSeller();
				}
				it++;
			}
		}
	}
	else if (commander == "Buyer")
	{
		cout << "orderID  " << "commodityID  " << "unitPrice "
			<< "number   " << "date\t" << "sellerID  " << endl;
		if (AllOrders.empty() != true)
		{
			while (it != AllOrders.end())
			{
				if (it->second.GetBuyerId() == BuyerId)
				{
					it->second.PrintBuyer();
				}
				it++;
			}
		}
	}
	else
	{
		cout << "The commander parameter of Print Order Function is Wrong!" << endl;
	}
	cout << "****************************************************************" << endl;
	return;
}
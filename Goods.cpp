#include "Goods.h"

//Good Method
Good::Good()
{
	_Id = "";
	_Name ="";
	_Price =0.0;
	_Stock =0;
	_Description ="";
	_SellerId ="";
	_UpTime ="";
	_Available = 0;
}
Good::Good(string Id, string Name, double Price, int Stock, string Descrip, string SellerId, string UpTime, string Available)
{
	_Id = Id;
	_Name = Name;
	Price = round(Price * 10) / 10.0;
	_Price = Price;
	_Stock = Stock;
	_Description = Descrip;
	_SellerId = SellerId;
	_UpTime = UpTime;
	if (Available == "onSale")
	{
		_Available = 1;
	}
	else if (Available == "removed")
	{
		_Available = 0;
	}
	else
	{
		cout << "The Good state in txt is Wrong! " << endl;
	}
}
Good::Good(string SellerId, string Name, double Price, int Stock, string Descrip,string Id)
{
	_Name = Name;
	_SellerId = SellerId;
	_Description = Descrip;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	_UpTime = to_string(timeinfo->tm_year+1900) + "-";
	if (timeinfo->tm_mon < 10) _UpTime += "0";
	_UpTime += (to_string(timeinfo->tm_mon+1)+"-");
	if(timeinfo->tm_mday<10) _UpTime += "0";
	_UpTime += to_string(timeinfo->tm_mday);
	_Stock = Stock;
	Price = round(Price * 10) / 10.0;
	_Price = Price;
	_Available = 1;
	_Id = Id;
}
Good::Good(const Good& g)
{
	_Id = g._Id;
	_Name = g._Name;
	_Price = g._Price;
	_Stock = g._Stock;
	_Description = g._Description;
	_SellerId = g._SellerId;
	_UpTime = g._UpTime;
	_Available = g._Available;
}

Good& Good::operator=(const Good& g)
{
	if (&g != this)
	{
		_Id = g._Id;
		_Name = g._Name;
		_Price = g._Price;
		_Stock = g._Stock;
		_Description = g._Description;
		_SellerId = g._SellerId;
		_UpTime = g._UpTime;
		_Available = g._Available;
	}
	return *this;
}

double Good::GetPrice() const
{
	return _Price;
}
void Good::SellGood(int num)
{
	_Stock -= num;
	Goods* All = Goods::GetInstance();
	All->ResetDocuGood();
	/*if (_Stock == 0)
		Disable();*/
	return;
}
void Good::changePrice(double Price)
{
	_Price = Price;
}
void Good::changeDescrip(string Descrip)
{
	_Description = Descrip;
}
void Good::Disable()
{
	_Available = 0;
}
int Good::GetStock()
{
	return _Stock;
}
string Good::GetName()
{
	return _Name;
}
string Good::GetSellerId()
{
	return _SellerId;
}
bool Good::GetAvailable()
{
	return _Available;
}

string Good::TransAvail()
{
	if (_Available)
	{
		return "onSale";
	}
	else
	{
		return "removed";
	}
}
string Good::OutInfo()
{
	string tmp = "";
	string P=to_string(_Price);
	P.erase(P.end() - 5, P.end());
	P.pop_back();
	tmp += (_Id + "," + _Name + "," + P + ","
		+ to_string(_Stock) + "," + _Description + ","
		+ _SellerId + "," + _UpTime + "," + TransAvail());
	return tmp;
}
void Good::LastPrint()
{
	cout << _Id << " " << _Name << " "
		<< fixed << setprecision(1) << _Price << " "
		<< _UpTime << "\t" << _Stock<<  "\t"
		<< _SellerId << "\t" << TransAvail()<<endl;
	return;
}
void Good::PrintAdmin()
{
	cout << _Id << " " << _Name << " "
		<< fixed << setprecision(1) << _Price << " "
		<< _UpTime << "\t" << _SellerId << "\t"
		<< _Stock << "\t" << TransAvail() << endl;;
	return;
}
void Good::PrintSeller()
{
	cout << _Id << " " << _Name << " "
		<< fixed << setprecision(1) << _Price << " "
		<< _Stock << "\t" << _UpTime << "\t"
		<< TransAvail()<<endl;
	return;
}
void  Good::PrintBuyer()
{
	cout << _Id << " " << _Name << " " 
		<< fixed << setprecision(1) << _Price
		<< "\t" << _UpTime << "\t"<<_SellerId<<endl;
	return;
}
void Good::PrintBuyerAccua()
{
	cout << "commodityID: " << _Id << endl
		<< "commodityName: " << _Name << endl
		<< "price: " << fixed << setprecision(1) << _Price << endl
		<< "addedDate: " << _UpTime << endl
		<< "description: " << _Description << endl
		<< "sellerID: " << _SellerId
		<<endl;
}
void Good::PrintWhenChangePri(string content)
{
	cout << "***********************************************" << endl
		<< "商品ID: " << _Id << endl
		<< "商品名称: " << _Name << endl
		<< "商品价格 " << content << endl
		<< "商品描述: " << _Description << endl
		<< "***********************************************" << endl;
	return;
}
void Good::PrintWhenChangeDes(string content)
{
	cout << "***********************************************" << endl
		<< "商品ID: " << _Id << endl
		<< "商品名称: " << _Name << endl
		<< "商品价格 " << fixed << setprecision(1) << _Price << endl
		<< "商品描述: " << content << endl
		<< "***********************************************" << endl;
	return;
}


//Goods Method

Goods* Goods::P_GeneralGoods = nullptr;
Goods* Goods::GetInstance()
{
	if (P_GeneralGoods == nullptr)
	{
		P_GeneralGoods = new Goods();
	}
	return P_GeneralGoods;
}
void Goods::DeleteInstance()
{
	if (P_GeneralGoods)
	{
		delete P_GeneralGoods;
		P_GeneralGoods = nullptr;
	}
}

//文件操作
void Goods::InputDocuGood()
{
	ifstream in_file;
	in_file.open("E:\\Project 1\\Project 1\\commodity.txt",
		ios::in);
	if (!in_file)
	{
		ofstream out_file;
		out_file.open("E:\\Project 1\\Project 1\\commodity.txt",
			ios::out);
		out_file.close();
		return;
	}
	AllGoods.clear();
	vector<string> Unit;
	string tmp="";
	getline(in_file,tmp);
	tmp.clear();
	while (getline(in_file, tmp))
	{
		while (tmp.find(",")!=string::npos)
		{
			string ke="";
			int pos = tmp.find(",");
			for (int i = 0; i < pos; i++)
			{
				ke.append(1,tmp[i]);
			}
			Unit.push_back(ke);
			tmp.erase(0,pos+1);
		}
		Unit.push_back(tmp);
		tmp.clear();
		AllGoods[Unit[0]] = Good(Unit[0],Unit[1],stod(Unit[2],0), stoi(Unit[3],0), Unit[4], Unit[5], Unit[6], Unit[7]);
		Unit.clear();
	}
	if (in_file.eof())
	{
		in_file.close();
	}
	else
	{
		cout << "Read Goods txt Wrong!" << endl;
	}
}

void Goods::ResetDocuGood()
{
	ofstream out_file;
	out_file.open("E:\\Project 1\\Project 1\\commodity.txt", ios::out);
	if (out_file.fail())
	{
		cout << "Open commodity.txt to write Error!" << endl;
		exit(-1);
	}
	out_file << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
	if (AllGoods.empty()!=true)
	{
		out_file << endl;
		map<string, Good>::iterator it = AllGoods.begin();
		while (it != AllGoods.end())
		{
			out_file << it->second.OutInfo() << endl;
			it++;
		}
	}
	out_file.close();
	InputDocuGood();
	return;
}
void Goods::UpGood(string SellerId, string Name, 
	double Price, int Stock, string Descrip)
{
	int k = GetAll()+1;
	string tp = "";
	for (int i = 100; i >= 1; i /= 10)
	{
		tp += to_string(k / i);
		k %= i;
	}
	string Id = "M" + tp;
	AllGoods[Id] = Good(SellerId, Name,Price,Stock,Descrip,Id);
	ResetDocuGood();
	return;
}


//小型函数
int Goods::GetGoodStock(string Id)
{
	return AllGoods[Id].GetStock();
}
string Goods::GetBySeller(string SellerId)
{
	string ke = "";
	for (map<string, Good>::iterator it = AllGoods.begin(); it != AllGoods.end(); it++)
	{
		if (it->second.GetSellerId() == SellerId)
		{
			ke += (it->first+",");
		}
	}
	return ke;
}
string Goods::GetSellerID(string Id)
{
	return AllGoods[Id].GetSellerId();
}
string Goods::GetPrice(string Id)
{
	string ke = "";
	ke = to_string(AllGoods[Id].GetPrice());
	ke.erase(ke.end()-5,ke.end());
	return ke;
}
void Goods::_SearchGood(string name, string commander)
{
	map<string,Good>::iterator it=AllGoods.begin();
	cout << "****************************************************************" << endl;
	if (commander == "Admin")
	{
		cout << "commodityID  commodityName\t   price\taddedDate\t sellerID\tnumber\tstate\n";
		while (it != AllGoods.end())
		{
			if (it->second.GetName().find(name) != string::npos)
			{
				PrintGoods("Admin", "specific", "", it->first);
			}
			it++;
		}
	}
	else if (commander == "Buyer")
	{
		cout << "commodityID  commodityName\t   price\t addedDate\t  sellerID\n";
		while (it != AllGoods.end())
		{
			if (it->second.GetAvailable())
			{
				if (it->second.GetName().find(name) != string::npos)
				{
					PrintGoods("Buyer", "specific", "", it->first);
				}
			}
			it++;
		}
	}
	else
	{
		cout << "The commander parameter of SearchGood is Wrong!" << endl;
	}
	cout << "****************************************************************" << endl;
	return;
}

bool Goods::CheckGoodId(string Id)
{
	return !(AllGoods.find(Id) == AllGoods.end());
}
void Goods::SellGood(string Id,int num)
{
	AllGoods[Id].SellGood(num);
	ResetDocuGood();
	return;
}
int Goods::GetAll()
{
	int num = 0;
	for (map<string,Good>::iterator it = AllGoods.begin(); it != AllGoods.end(); it++)
	{
		num++;
	}
	return num;
}

void Goods::ChangeGoodPrice(string Id, double Price)
{
	AllGoods[Id].changePrice(Price);
	ResetDocuGood();
	return;
}
void Goods::ChangeGoodDescrip(string Id, string Descrip)
{
	AllGoods[Id].changeDescrip(Descrip);
	ResetDocuGood();
	return;
}
void Goods::DisableGood(string Id)
{
	AllGoods[Id].Disable();
	ResetDocuGood();
	return;
}

void Goods::PrintWhenChange(string Id,string Pattern,string content)
{
	if (Pattern == "Price")
	{
		AllGoods[Id].PrintWhenChangePri(content);
		return;
	}
	if (Pattern == "Descrip")
	{
		AllGoods[Id].PrintWhenChangeDes(content);
	}
	return;
}
void Goods::PrintGoods(string Commander, string Pattern, string UserID , string Id)
{
	if (Pattern == "Last")
	{
		cout << "****************************************************************" << endl;
		cout << "commodityID  commodityName\t   price\taddedDate\t number\tsellerID\tstate\n";
		AllGoods[Id].LastPrint();
		return;
	}
		int decision;
		map<string,Good>::iterator it = AllGoods.begin();
		if (Commander == "Admin")
		{
			decision = 1;
		}
		else if (Commander == "Seller")
		{
			decision = 2;
		}
		else if (Commander == "Buyer")
		{
			decision = 3;
		}
		else
		{
			cout << "The Commander parameter of print function is Wrong!" << endl;
			return;
		}
		switch (decision)
		{
		case 1:
			cout << "****************************************************************" << endl;
			cout << "commodityID  commodityName\t   price\taddedDate\t sellerID\tnumber\tstate\n";
			if (AllGoods.empty() != true)
			{
				if (Pattern == "specific")
				{
					AllGoods[Id].PrintAdmin();
					break;
				}
				else if (Pattern == "general")
				{
					
					while (it != AllGoods.end())
					{
						it->second.PrintAdmin();
						it++;
					}
					break;
				}
				else
				{
					cout << "The Pattern parameter of print function is Wrong!" << endl;
					break;
				}
			}
			break;
		case 2:
			cout << "****************************************************************" << endl;
			cout << "commodityID  commodityName\t   price\tnumber\t addedDate\t  state\n";
			if (AllGoods.empty() != true)
			{
				if (Pattern == "specific")
				{
					AllGoods[Id].PrintSeller();
					break;
				}

				else if (Pattern == "general")
				{
					while (it != AllGoods.end())
					{
						if (it->second.GetSellerId() == UserID)
						{
							it->second.PrintSeller();
							it++;
						}
					}
					break;
				}
				else
				{
					cout << "The Pattern parameter of print function is Wrong!" << endl;
					break;
				}
			}
			break;
		case 3:
			if (AllGoods.empty() != true)
			{
				if (Pattern == "specific")
				{
					cout << "****************************************************************" << endl;
					AllGoods[Id].PrintBuyerAccua();
					break;
				}
				else if (Pattern == "general")
				{
					cout << "****************************************************************" << endl;
					cout << "commodityID  commodityName\t   price\t addedDate\t  sellerID\n";
					while (it != AllGoods.end())
					{
						if (it->second.GetAvailable())
						{
							it->second.PrintBuyer();
						}
						it++;
					}
					break;
				}
				else if (Pattern == "Accura")
				{
					cout << "****************************************************************" << endl;
					AllGoods[Id].PrintBuyerAccua();
					break;
				}
				else
				{
					cout << "The Pattern parameter of print function is Wrong!" << endl;
					break;
				}
			}
			break;
		}
	cout << "****************************************************************" << endl;
	return;
}
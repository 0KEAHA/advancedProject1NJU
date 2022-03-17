#include "User.h"

void UpCommand(string command)
{
	ofstream out_file;
	out_file.open("E:\\Project 1\\Project 1\\command.txt", ios::app);
	if (out_file.fail())
	{
		cout << "Open command.txt to write Error!" << endl;
		exit(-1);
	}
	string _UpTime = "";
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	_UpTime = to_string(timeinfo->tm_year + 1900) + "-";
	if (timeinfo->tm_mon < 10) _UpTime += "0";
	_UpTime += (to_string(timeinfo->tm_mon+1) + "-");
	if (timeinfo->tm_mday < 10) _UpTime += "0";
	_UpTime += to_string(timeinfo->tm_mday);
	_UpTime += " ";
	if (timeinfo->tm_hour < 10) _UpTime += "0";;
	_UpTime += (to_string(timeinfo->tm_hour) + ":");
	if (timeinfo->tm_min < 10) _UpTime += "0";;
	_UpTime += (to_string(timeinfo->tm_min) + ":");
	if (timeinfo->tm_sec < 10) _UpTime += "0";;
	_UpTime += (to_string(timeinfo->tm_sec) + ":");
	out_file << _UpTime << command << endl;
	return;
}

//指令解析
void Admin::AnaSQL(string command)
{
	string Keep = command;
	if (Keep.empty())
	{
		return;
	}
	else
	{
		//字符串拆解
		vector<string> UnitCommand;
		string::size_type pos = Keep.find(" ");
		while (pos != string::npos)
		{
			string ke = "";
			for (int i = 0; i < pos; i++)
			{
				ke.append(1, Keep[i]);
			}
			UnitCommand.push_back(ke);
			Keep.erase(0, pos + 1);
			pos = Keep.find(" ");
		}
		UnitCommand.push_back(Keep);
		Keep.clear();
		vector<string>::iterator it = UnitCommand.begin();
		if (*it == "SELECT")
		{
			try
			{
				it++;
				if (*it != "*" || (*(++it) != "FROM")) throw 1;
				if (*(it + 1) == "order")
				{
					UpCommand(command);
					_CheckDeals();
					return;
				}
				if (*(it + 1) == "user")
				{
					UpCommand(command);
					_CheckUsers();
					return;
				}
				if ((*(++it) == "commodity"))
				{
					++it;
					if (it == UnitCommand.end())
					{
						UpCommand(command);
						_CheckGoods();
						return;
					}
					if (*it == "WHERE" && (*(++it) == "commodityName") && (*(++it) == "CONTAINS"))
					{
						UpCommand(command);
						_SearchGoods(*(++it));
						return;
					}
					else
					{
						throw 1;
					}
				}
				else
				{
					throw 1;
				}

			}
			catch (int)
			{
				cout << "The Admin SELECT command is Wrong!" << endl;
				return;
			}
		}
		else if (*it == "UPDATE")
		{
			it++;
			if (*it == "commodity")
			{
				UpCommand(command);
				_DisableGood(*(UnitCommand.end()-1));
				return;
			}
			if (*it == "user")
			{
				UpCommand(command);
				_DisableUser(*(UnitCommand.end()-1));
				UpCommand("UPDATE commodity  SET  state = removed WHERE sellerID CONTAINS "+ *(UnitCommand.end()-1));
				Goods* allgood = Goods::GetInstance();
				string AKGood = allgood->GetBySeller(*(UnitCommand.end()-1));
				vector<string> UnitGood;
				string::size_type pos = AKGood.find(",");
				while (pos != string::npos)
				{
					string ke = "";
					for (int i = 0; i < pos; i++)
					{
						ke.append(1, Keep[i]);
					}
					UnitGood.push_back(ke);
					Keep.erase(0, pos + 1);
					pos = AKGood.find(",");
				}
				if (!UnitGood.empty())
				{
					for (vector<string>::iterator it = UnitGood.begin(); it != UnitGood.end(); it++)
					{
						_DisableGood(*it);
					}
				}
				cout << "已封禁！" << endl << endl;
				return;
			}
		}
	}
}



void User::AnaSQL(string command)
{
	string Keep = command;
	if (Keep.empty())
	{
		return;
	}
	else
	{
		//字符串拆解
		vector<string> UnitCommand;
		string::size_type pos = Keep.find(" ");
		while (pos != string::npos)
		{
			string ke = "";
			for (int i = 0; i < pos; i++)
			{
				ke.append(1, Keep[i]);
			}
			UnitCommand.push_back(ke);
			Keep.erase(0, pos + 1);
			pos = Keep.find(" ");
		}
		UnitCommand.push_back(Keep);
		Keep.clear();
		vector<string>::iterator it = UnitCommand.begin();
		if (*it == "SELECT")
		{
			it++; it++; it++;
			if (*it == "commodity")
			{
				CheckMyGood();
				UpCommand(command);
				return;
			}
			else if (*it == "order")
			{
				CheckMyOrder();
				UpCommand(command);
				return;
			}
			else
			{
				cout << "Seller Select command is wrong!" << endl;
				return;
			}
		}
		else if (*it == "INSERT")
		{
			it += 5;
			string des = "";
			vector<string>::iterator keep = it;
			++++++it;
			for (; it != UnitCommand.end() - 1; it++)
			{
				des += *it;
			}
			AddGood(*keep, stod(keep[1]), stoi(keep[2]), des);
			UpCommand(command);
			return;
		}
		else if (*it == "UPDATE")
		{
			it += 3;
			if (*it == "price")
			{
				++++it;
				ChangeMyGoodPrice(*(UnitCommand.end()-1),stod(*it));
				UpCommand(command);
				cout << "修改成功！" << endl << endl;
				return;
			}
			else if (*it == "description")
			{
				string des = "";
				++++it;
				for (; it != UnitCommand.end() - 4; it++)
				{
					des += *it;
					des += " ";
				}
				des.pop_back();
				ChangeMyGoodDescrip(*(UnitCommand.end()-1),des);
				UpCommand(command);
				cout << "修改成功！" << endl << endl;
				return;
			}
			else if (*it == "state")
			{
				RemoveMyGood(*(UnitCommand.end() - 1));
				UpCommand(command);
				cout << "已下架！" << endl << endl;
				return;
			}
			else
			{
				cout << "The seller Up command is Wrong!" << endl << endl;
				return;
			}
		}
		else
		{
			cout << "The seller command is Wrong!" << endl << endl;
			return;
		}
	}
}
void User::SPAnaSQL(string command)
{
	string Keep = command;
	if (Keep.empty())
	{
		return;
	}
	else
	{
		//字符串拆解
		vector<string> UnitCommand;
		string::size_type pos = Keep.find(" ");
		while (pos != string::npos)
		{
			string ke = "";
			for (int i = 0; i < pos; i++)
			{
				ke.append(1, Keep[i]);
			}
			UnitCommand.push_back(ke);
			Keep.erase(0, pos + 1);
			pos = Keep.find(" ");
		}
		UnitCommand.push_back(Keep);
		Keep.clear();
		vector<string>::iterator it = UnitCommand.begin();
		if (*it == "SELECT")
		{
			it += 3;
			if (*it == "commodity")
			{
				if (it == UnitCommand.end() - 1)
				{
					UpCommand(command);
					CheckGood();
					return;
				}
				it += 2;
				if (*it == "commodityID")
				{
					UpCommand(command);
					CheckGoodAccura(*(UnitCommand.end() - 1));
					return;
				}
				if (*it == "commodityName")
				{
					UpCommand(command);
					SearchGood(*(UnitCommand.end() - 1));
					return;
				}
				else
				{
					cout << "The select command Buyer is Wrong!" << endl << endl;
					return;
				}
			}
			if (*it == "order")
			{
				it++;
				if (it == UnitCommand.end())
				{
					UpCommand(command);
					CheckOrder();
					return;
				}
				else
				{
					cout << "The Buyer Select Buyer is Wrong!" << endl << endl;
					return;
				}
			}
			else
			{
				cout << "Buyer Select Buyer is Wrong!" << endl << endl;
				return;
			}
		}
		else if (*it == "INSERT")
		{
			it += 5;
			string tmp = *it;
			vector<string> UnitPara;
			string::size_type pos = tmp.find(",");
			while (pos != string::npos)
			{
				string ke = "";
				for (int i = 0; i < pos; i++)
				{
					ke.append(1, tmp[i]);
				}
				UnitPara.push_back(ke);
				tmp.erase(0, pos + 1);
				pos = tmp.find(",");
			}
			UnitPara.push_back(tmp);
			tmp.clear();
			vector<string>::iterator po = UnitPara.begin();
			double balance = stod(GetMoney());
			if (balance < stod(calculator(po[2] + "*" + po[3])))
			{
				cout << "对不起，您的余额不足，请充值！" << endl << endl;
				return;
			}
			else
			{
				BuyGood(po[0], po[1], po[2], po[3], po[4], po[5]);
				UpCommand(command);
				UpCommand("UPDATE commodity SET number = "+ po[3]+" WHERE commodityID CONTAINS "+ po[1]);
				Goods* Ag = Goods::GetInstance();
				if (Ag->GetGoodStock(po[1]) == 0)
				{
					AnaSQL("UPDATE commodity SET state = removed WHERE commodityID CONTAINS "+ po[1]);
				}
				cout << "购买成功!" << endl << endl;
				return;
			}
		}
	}
}
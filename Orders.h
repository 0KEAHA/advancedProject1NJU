#define COrder
#ifndef HGen
#define HGen
#include "General.h"
#endif

class Order
{
private:
	string _OrderId;
	string _GoodId;
	string _Num;
	string _Date;
	string _Price;
	string _SellerId;
	string _BuyerId;
public:
	Order();
	Order(string, string, double, int, string, string);
	Order(string, string, string, string, string, string, string);
	Order(const Order&);
	Order& operator=(const Order&);
	void PrintAdmin();
	void PrintSeller();
	void PrintBuyer();
	string GetSellerId();
	string GetBuyerId();
	string OutInfo();
};
class Orders
{
private:
	Orders(){};
	static Orders* P_GenOrders;
	map<string, Order> AllOrders;
public:
	static Orders* GetInstance();
	static void DeleteInstance();
	int GetAll();
	void ResetDocuOrder();
	void InputDocuOrder();
	void UpOrder(string,string,string,string,string,string,string);
	void PrintOrders(string, string SellerId="", string BuyerId="");
};


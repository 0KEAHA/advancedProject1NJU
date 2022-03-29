#define CCart

#ifndef HGen
#define HGen
#include "General.h"
#endif
#ifndef HCla
#define HCla
#include "ClassGen.h"
#endif
class Cart
{
private:
	string _UserId;
	vector<pair<string,int> > _UnitCommdity;
public:
	Cart();
	Cart(string UserId);
	Cart(const Cart&);
	Cart(string UserId, vector<pair<string, int> >);
	
	Cart& operator=(const Cart&);
	void AddCart(string CmmodityId,int num);
	void BuyAll();
	void ClearDis();
	void Erase();
	void DeletSome(string CommodityId);
	void ShowAll();


	string Outinfo();
	bool CheckId(string Id);

};
class Carts
{
private:
	string _CurrUserId;
	static Carts* P_AllCarts;
	map<string, Cart> AllCarts;
	Carts() {};
public:
	static Carts* GetInstance();
	void DeleteInstance();

	//ÎÄ¼þ²Ù×÷
	void InputDocuCarts();
	void ResetDocucarts();

	void SetUserId(string);

	void GovCarts();
	void AddCart();
	void BuyAll();
	void ClearDis();
	void Erase();
	void DeletSome();
	void ShowAll();
};
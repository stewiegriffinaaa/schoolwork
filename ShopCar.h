#pragma once
#include"Time.h"
#include"Consume.h"
#include"goods.h"
#include<vector>
#include<time.h>
using namespace std;
#include<sstream>
class ShopCar
{
	string ShopCarNum;
	string ConsumeNum;
	Time start;
	Time end;
	vector<Goods> num;
	vector<Time> addnum;
public:
	ShopCar();
	ShopCar(Consume example);
	void add(Goods sample);
	void dec(Goods type, int numb);
	string& getShopCarNum();
	string& getConsumeNum();
	Time& getStart();
	Time& getEnd();
	vector<Goods>& getNum();
	vector<Time>& getAddnum();
	void CompleteCut(Goods type);
	~ShopCar();
	friend ostream& operator<<(ostream& out, ShopCar& example);
};
ostream& operator<<(ostream& out, ShopCar& example);

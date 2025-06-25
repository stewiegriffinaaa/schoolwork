#pragma once
#include"Time.h"
#include"Consume.h"
#include"Goods.h"
#include<vector>
#include<sstream>
using namespace std;
class ShopCar:public Consume
{
protected:
  int ShopCarNum;
  int ConsumeNum;
  Time start;
  Time end;
  vector<Goods> num;
  vector<Time> addnum;
public:
  ShopCar(int _num,string _name,char _class,string _email,Time _Start,int _ShopCar,int _ConsumeNum,Time _start,Time _end);
  ostringstream& show(ostringstream& out);
  void add(Goods sample);
  void dec(Goods type,int numb);
  int getShopCarNum();
  int getConsumeNum();
  Time getStart();
  Time getEnd();
  vector<Goods> getNum();
  vector<Time> getAddnum();
  ~ShopCar();
};

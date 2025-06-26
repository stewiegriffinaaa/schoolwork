#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<list>
using namespace std;
class Goods {
	//string type = "Goods";
	string id;
	string name;
	double price;
	int num;
	string goodtype;
	string time;
public:
	Goods(string id, string name, double price, int num, string type, string time) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->num = num;
		this->goodtype = type;
		this->time = time;
	}
	Goods() {}
	string getId() const {
		return id;
	}
	string getName() const {
		return name;
	}
	double getPrice() const {
		return price;
	}
	int getNum() const {
		return num;
	}
	string getGoodtype() const {
		return goodtype;
	}
	string getTime() const {
		return time;
	}
	//		string getTime() {
	//			return time;
	//		}
	void setId(string id) {
		this->id = id;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPrice(double price) {
		this->price = price;
	}
	void setNum(int num) {
		this->num = num;
	}
	void setGoodtype(string goodtype) {
		this->goodtype = goodtype;
	}
	void settime(string time) {
		this->time = time;
	}
	~Goods() {}
	friend istream& operator>>(istream& in, Goods& obj) {
		//			cout << "将按编号、名称、价格、库存量、分类、上架时间,输入商品信息" << endl;
		in >> obj.id >> obj.name >> obj.price >> obj.num >> obj.goodtype >> obj.time;
		return in;
	}

	friend ostream& operator<<(ostream& out, const Goods& obj) {
		out << obj.id << " " << obj.name << " " << obj.price << " " << obj.num << " " << obj.goodtype << " " << obj.time;
		return out;
	}


};

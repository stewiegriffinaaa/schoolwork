#pragma once
#include"Time.h"
#include<string>
using namespace std;
class Consume
{
protected:
	string num;
	string name;
	char _class;
	string email;
	Time _start;
public:
	Consume();
	Consume(string _num, string _name,char _Class, string _email, Time _Start);
	string getNum();
	friend ostream& operator<<(ostream& out, Consume& example);
	friend istream& operator>>(istream& in, Consume& example);
};
ostream& operator<<(ostream& out, Consume& example);
istream& operator>>(istream& in, Consume& example);

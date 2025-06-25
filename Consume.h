#pragma once
#include"Time.h"
#include<string>
using namespace std;
class Consume
{
protected:
  int num;
  string name;
  char _class;
  string email;
  Time _start;
public:
  Consume();
  Consume(int _num,string _name,char _Class,string _email,Time _Start);
  friend ostream& operator<<(ostream& out, Consume& example);
};
ostream& operator<<(ostream& out, Consume& example);

#include"Consume.h"
#include<string>
using namespace std;
Consume::Consume(){

}
Consume::Consume(int _num,string _name,char _Class,string _email,Time _Start){
  this->num = _num;
  this->name = _name;
  this->_class = _Class;
  this->email = _email;
  this->_start = _Start;
}
ostream& operator<<(ostream& out, Consume& example){
  out << example.num << " " << example.name << " "  << example._class << example.email << " " << example._start;
  return out;
}

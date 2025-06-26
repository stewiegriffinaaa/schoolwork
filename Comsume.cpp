#include"Consume.h"
#include<string>
#include"Time.h"
using namespace std;
Consume::Consume(string _num, string _name, char _Class, string _email, Time _Start):_start(_Start) {
	this->num = _num;
	this->name = _name;
	this->_class = _Class;
	this->email = _email;
}
ostream& operator<<(ostream& out, Consume& example) {
	out << example.num << " " << example.name << " " << example._class << example.email << " " << example._start;
	return out;
}
istream& operator>>(istream& in, Consume& example){
	in >> example.num >> example.name >> example._class >> example.email >> example._start;
	return in;
}//修改点六

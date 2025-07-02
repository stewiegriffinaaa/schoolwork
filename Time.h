#pragma once
#include<iostream>
using namespace std;
struct Time
{
	int year = 0;
	int month = 0;
	int day = 0;
};
inline ostream& operator<<(ostream& out, Time& num) {
	out << num.year  << "-" << num.month << "-" << num.day;
	return out;
}
inline istream& operator>>(istream& in, Time& num) {
	char a, b;
	in >> num.year  >> a >>  num.month >> b >> num.day;
	return in;
}//修改点七

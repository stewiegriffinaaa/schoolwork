#pragma once
#include<iostream>
using namespace std;
struct Time
{
  int year = 0;
  int month = 0;
  int day = 0;
};
ostream& operator<<(ostream& out,Time& num){
  out << num.year << "-" << num.month << "-" << num.day;
  return out;
} 

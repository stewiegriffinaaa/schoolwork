#pragma once
#include"ShopCarDate.h"
using namespace std;
void ConsumeDec(ShopCar& example, ShopLinked& example1, Goods type, int numb) {
    example.dec(type, numb);
    example1.pop(type, numb);
}
void ConsumeAdd(ShopCar& example, ShopLinked& example1, Goods type, int numb) {
    example1.Insert(type, numb);
    for (int i = 0; i < numb; i++) {
        example.add(type);
    }
}
void ComDec(vector<ShopCar>& example,vector<ShopLinked>& example1,Goods type) {
    for (vector<ShopCar>::iterator i = example.begin(); i != example.end(); i++) {
        i->CompleteCut(type);
    }
    for (vector<ShopLinked>::iterator t = example1.begin(); t != example1.end(); t++) {
        t->CompleteDec(type);
    }
}
//总接口彻底删除函数（服务与系统）

#pragma once
#include"ShopCarDate.h"
using namespace std;
void ConsumeDec(ShopCar example, ShopLinked example1, Goods type, int numb) {
    example.dec(type, numb);
    example1.pop(type, numb);
}
void ConsumeAdd(ShopCar example, ShopLinked example1, Goods type, int numb) {
    example1.Insert(type, numb);
    for (int i = 0; i < numb; i++) {
        example.add(type);
    }
}
void ComDec(ShopCar example,ShopLinked example1,Goods type) {
    example.CompleteCut(type);
    example1.popTail();
}
//总接口彻底删除函数（服务与系统）

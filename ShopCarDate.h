#pragma once
#include"Goods.h"
#include"ShopCar.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Node
{
  Goods type;
  int count;
  Node *dire;
public:
  Node(){
    this->count = 0;
  }
  Node(Goods type,int num){
    this->type = type;
    this->count = num;
  }
  friend class ShopLinked;
};
class ShopLinked
{
  string StreamDate;
  int signal;
  double sum;
  Node head;
public:
  ShopLinked(ShopCar& example,string inf){
    StreamDate = inf;
    signal = example.getShopCarNum();
    this->sum = 0;
    for(vector<Goods>::iterator it = example.getNum().begin();it != example.getNum().end();it++){
      this->Insert(*it,1);
      sum += (*it).getPrice();
    }
  }
  void setSum(){
    sum = 0;
    Node*p = head.dire;
    while(p->dire != NULL){
      sum += p->count*p->type.getPrice();
      p = p->dire;
    }
    sum += p->count*p->type.getPrice();
  }
  void Insert(Goods ty,int num){
    Node*p = head.dire;
    bool aw = 1;
    while(p->dire != NULL){
      if(p->type.getName() == ty.getName()){
        p->count += num;
        aw = 0;
        break;
      }
      p = p->dire;
    }
    if(aw){
      Node*mid = new Node(ty,num);
      p->dire = mid;
    }
  }
  bool is_empty(){
    if(head.dire == NULL)
      return 1;
    return 0;
  }
  bool pop(Goods ty,int num){
    Node*p = &head;
    if(this->is_empty() == 1)
      return 0;
    while(p->dire->dire != NULL){
      if(p->dire->type.getName() == ty.getName()){
        if(p->dire->count > num){
          p->dire->count -= num;
          return 1;
        }
        if(p->dire->count == num){
          Node *q = p->dire->dire;
          delete p->dire;
          p->dire = q;
          return 1;
        }
      }
      p = p->dire;
    }
    if(p->dire->type.getName() == ty.getName()){
      if(p->dire->count > num){
        p->dire->count -= num;
        return 1;
      }
      if(p->dire->count == num){
        delete p->dire;
        p->dire = NULL;
        return 1;
      }
    }
    return 0;
  }
  ostringstream& show(ostringstream& out){
    Node*p = head.dire;
    while(p->dire != NULL){
      out << p->type << "总计: "<< p->count << "个" << endl;
      p = p->dire;
    }
    out << "总计应付款: " << this->sum;
    return out;
  }
  bool popTail(){
    Node*p = &head;
    if(this->is_empty())
      return 1;
    while(p->dire->dire != NULL){
      p = p->dire;
    }
    delete p->dire;
    p->dire = NULL;
    return 0;
  }
  ~ShopLinked(){
    while(this->is_empty() == 0){
      this->popTail();
    }
  }
};








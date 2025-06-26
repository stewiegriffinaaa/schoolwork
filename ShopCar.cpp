#include"ShopCar.h"
using namespace std;
#include<sstream>
ShopCar::ShopCar(string _num, string _name, char _class, string _email, Time _Start, int _ShopCar, int _ConsumeNum, Time _start, Time _end) : Consume(_num, _name, _class, _email, _Start)
{
    this->ShopCarNum = _ShopCar;
    this->ConsumeNum = _ConsumeNum;
    this->start = _start;
    this->end = _end;
}
ostringstream& ShopCar::show(ostringstream& out)
{
    int i = 0;
    out << "购物车" << ShopCarNum << "号 " << "顾客" << ConsumeNum << "号 " << start << "至" << end << endl;
    for (vector<Goods>::iterator it = num.begin(); it != num.end(); it++) {
        out << *it << " " << "添入时间: " << addnum[i] << endl;
        i++;
    }
    return out;
}
void ShopCar::add(Goods sample)
{
    time_t now = time(NULL);
    tm local_time = {};
    localtime_s(&local_time,&now);
    Time mid;
    mid.year = local_time.tm_year + 1900;
    mid.month = local_time.tm_mon + 1;
    mid.day = local_time.tm_mday;
    addnum.push_back(mid);
    num.push_back(sample);
}
void ShopCar::dec(Goods type, int numb) {
    for (vector<Goods>::iterator it = num.begin();it != num.end();it++) {
        if ((*it).getId() == type.getId()) {
            int mid = it - num.begin();           //保持时间删除和商品删除的同步性（修改点）
            vector<Time>::iterator it1 = addnum.begin() + mid;
            addnum.erase(it1);
            it = num.erase(it);
            numb--;
        }
        if (numb == 0) {
            break;
        }
    }
}
void ShopCar::CompleteCut(Goods type) {
    for (vector<Goods>::iterator it = num.begin(); it != num.end(); it++) {
        if ((*it).getId() == type.getId()) {
            int mid = it - num.begin();          //补充彻底删除函数，主导系统删除任务（修改点二）
            vector<Time>::iterator it1 = addnum.begin() + mid;
            addnum.erase(it1);
            it = num.erase(it);
        }
    }
}
int ShopCar::getShopCarNum() {
    return ShopCarNum;
}
int ShopCar::getConsumeNum() {
    return ConsumeNum;
}
Time ShopCar::getStart() {
    return start;
}
Time ShopCar::getEnd() {
    return end;
}
vector<Goods> ShopCar::getNum() {
    return num;
}
vector<Time> ShopCar::getAddnum() {
    return addnum;
}
ShopCar::~ShopCar() {}

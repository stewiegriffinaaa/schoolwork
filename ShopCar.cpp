#include"ShopCar.h"
using namespace std;
#include<sstream>
#include<time.h>
ShopCar::ShopCar() {            //必要性观察

}
ShopCar::ShopCar(Consume example)
{
    this->ShopCarNum = example.getNum();
    this->ConsumeNum = example.getNum();
    time_t now = time(NULL);
    tm local_time = {};
    localtime_s(&local_time, &now);
    Time mid;
    mid.year = local_time.tm_year + 1900;
    mid.month = local_time.tm_mon + 1;
    mid.day = local_time.tm_mday;
    this->start = mid;
    Time mid2;
    mid2.year = mid.year + 20;
    mid2.month = mid.month;
    mid2.day = mid.day;
    this->end = mid2;
}
ostream& operator<<(ostream& out,ShopCar& example)
{
    int i = 0;
    for (vector<Goods>::iterator it = example.num.begin(); it != example.num.end(); it++) {
        out << example.ShopCarNum << " " << example.start << " " << example.end << " " << it->getId() << " " << example.addnum[i] << endl;
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
 //   cout << "添加成功" << endl;  //wwwwwwwwwwwwwwwwww
 //   cout << num.size() << endl;
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
    // 使用迭代器遍历商品列表
    for (auto it = num.begin(); it != num.end(); ) {
        if (it->getId() == type.getId()) {
            // 计算当前元素在vector中的位置
            size_t index = it - num.begin();

            // 删除对应的时间记录
            addnum.erase(addnum.begin() + index);

            // 删除当前商品，并更新迭代器
            it = num.erase(it);
        }
        else {
            // 如果没有删除元素，正常推进迭代器
            ++it;
        }
    }
}
string& ShopCar::getShopCarNum() {
    return ShopCarNum;
}
string& ShopCar::getConsumeNum() {
    return ConsumeNum;
}
Time& ShopCar::getStart() {
    return start;
}
Time& ShopCar::getEnd() {
    return end;
}
vector<Goods>& ShopCar::getNum() {
    return num;
}
vector<Time>& ShopCar::getAddnum() {
    return addnum;
}
ShopCar::~ShopCar() {}

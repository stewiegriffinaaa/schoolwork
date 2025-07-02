#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include <algorithm>
#include<unordered_map>
#include <windows.h>
#include"goods.h"
#include"goodsTable1.h"
#include"Consume.h"
#include"ShopCarDate.h"
#include"ShopCar.h"
#include"TablesOP.h"
//先读出所有文件到队列里面，文本文件储存方式应该是 xxx xx
using namespace std;
#include<sstream>
#include "ConsumeControl.h"
void showgoods(Goods& a);
void showgoodTables(GoodsTable& a);
Goods getgoods(vector<Goods> num, string id);
//bool SearchById(string id, Goods temp);/*注：这里面有多次读取文件操作，之后要试试能不能给他封装到一个函数中当作形参传进去，否则太消耗性能*/
//bool SearchByName(string name, Goods temp);
void showgoods(Goods& a) {
    cout << "商品名称" << a.getName() << " 商品编号" << a.getId() << " 商品价格" << a.getPrice() << " 商品库存" << a.getNum() << " 商品上架时间" << a.getTime() << endl;
}
void showgoodTables(GoodsTable& a) {
    cout << "目录名称" << a.getName() << " 目录编号" << a.getId() << " 目录子节点等级" << a.getLevel() << " 子目录数量" << a.getNum() << " 目录时间" << a.getTime() << endl;
}
Goods getgoods(vector<Goods> num, string id) {
    for (auto it = num.begin(); it != num.end(); it++) {
        if (id == it->getId()) {
            return *it;
        }
    }
}
ShopCar& getShopCar(vector<ShopCar>& customer1,vector<ShopLinked>& customer2,Consume& example) {
    if (customer1.empty()) {
        ShopCar _example(example);
        customer1.push_back(_example);
        ShopLinked _example1(_example);
        customer2.push_back(_example1);
        return customer1.back();
    }
    for (auto it = customer1.begin(); it != customer1.end(); it++) {
        if (example.getNum() == it->getShopCarNum() ){
            return *it;
        }
    }
    ShopCar _example(example);
    customer1.push_back(_example);
    ShopLinked _example1(_example);
    customer2.push_back(_example1);
    return customer1.back();
}
ShopLinked& getShopLinked(vector<ShopLinked>& customer2, ShopCar& example) {
    for (auto it = customer2.begin(); it != customer2.end(); it++) {
        if (example.getShopCarNum() == it->getStream())
            return *it;
    }
}




int main() {
    cout << "\t\t\t\t\t网上购物系统祝您使用愉快" << endl;
    string str;
    fstream file;
    string op;
    cout << "\n请选择操作类型：\n";
    cout << "请输出你要操作的业务\nA:顾客\nB:商品\nC:商品分类目录\nF:保存此次操作并退出" << endl;
    cout << "请输入选项（A/B/C/F）: ";
    cin >> str;
    while (str != "F") {
        vector<Goods> goods;
        Goods temp1;
        file.open("goods.txt", ios::in);
        while (file >> temp1) {
            goods.push_back(temp1);
        }
        file.close();
        vector<Consume> customer;
        vector<ShopCar> customer1;
        vector<ShopLinked> customer2;
        Consume mid;
        file.open("Customers.txt", ios::in);
        while (file >> mid) {
            customer.push_back(mid);
        }
        file.close();
        file.open("ShopCarAll.txt", ios::in);
        ShopCar currentCar;
        string currentShopCarNum;
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string shopCarNum, goodsId;
            Time start, end, addTime;

            if (iss >> shopCarNum >> start >> end >> goodsId >> addTime) {
                // 当检测到新的购物车编号时
                if (currentShopCarNum != shopCarNum) {
                    // 如果不是首次处理，添加前一个购物车到容器
                    if (!currentCar.getShopCarNum().empty()) {
                        customer1.push_back(currentCar);
                        //           cout << "添加购物车: " << currentShopCarNum << endl;
                    }

                    // 创建新的购物车对象
                    currentCar = ShopCar();
                    currentCar.getShopCarNum() = shopCarNum;
                    currentCar.getConsumeNum() = shopCarNum;
                    currentCar.getStart() = start;
                    currentCar.getEnd() = end;
                    currentShopCarNum = shopCarNum;
                }

                // 添加商品到当前购物车
                Goods foundGoods = getgoods(goods, goodsId);
                if (foundGoods.getId() != "") {
                    currentCar.getNum().push_back(foundGoods);
                    currentCar.getAddnum().push_back(addTime);
                }
            }
        }
        if (!currentCar.getShopCarNum().empty()) {
            customer1.push_back(currentCar);
            //   cout << "添加购物车: " << currentShopCarNum << endl;
        }
        file.close();
        for (vector<ShopCar>::iterator it = customer1.begin(); it != customer1.end(); it++) {
            ShopLinked _mid(*it);
            customer2.push_back(_mid);
        }
        if (str == "A") { //顾客操作
            cout << " 请输入你想操作的顾客信息 " << endl;
            Consume example;
            cin >> example;
            bool flag = false;
            for (vector<Consume>::iterator it = customer.begin(); it != customer.end(); it++) {
                if (example.getNum() == (*it).getNum()) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                cout << "已查询到此顾客信息" << endl;
                cout << "请选择你想要的操作：" << endl;
                cout << "A.向该顾客购物车中增加商品" << endl << "B.向该顾客购物车中减少商品" << endl;
                cout << "C.删除该顾客信息" << endl;
                cout << "D.展现该用户购物车统计信息" << endl;
                string choice;
                cin >> choice;
                if (choice == "A") {
                    string mid = "继续";
                    while (mid != "停止") {

                        Goods type;
                        int numb;
                        string id;
                        cout << "请输入商品编号" << endl;
                        cin >> id;
                        type = getgoods(goods, id);
                        cout << "请输入新加入的商品数量" << endl;
                        cin >> numb;
                        getShopCar(customer1,customer2, example);
                        ConsumeAdd(getShopCar(customer1,customer2,example),getShopLinked(customer2, getShopCar(customer1,customer2, example)),type,numb);
                        cout << "继续还是停止？（输入“继续”或者“停止”）" << endl;
                        cin >> mid;
                        while (mid != "继续" && mid != "停止") {
                            cout << "输入错误内容，请重新输入" << endl;
                            cin >> mid;
                        }
                    }
                }
                if (choice == "B") {
                    string mid = "继续";
                    while (mid != "停止") {
                        Goods type;
                        int numb;
                        string id;
                        cout << "请输入商品编号" << endl;
                        cin >> id;
                        type = getgoods(goods, id);
                        cout << "请输入要削减的商品数量" << endl;
                        cin >> numb;
                        ConsumeDec(getShopCar(customer1,customer2, example), getShopLinked(customer2, getShopCar(customer1,customer2, example)), type, numb);
                        for (vector<ShopCar>::iterator it = customer1.begin(); it != customer1.end(); it++) {
                            if (it->getNum().size() == 0) {
                                it = customer1.erase(it);
                            }
                        }
                        cout << "继续还是停止？（输入“继续”或者“停止”）" << endl;
                        cin >> mid;
                        while (mid != "继续" && mid != "停止") {
                            cout << "输入错误内容，请重新输入" << endl;
                            cin >> mid;
                        }
                    }
                }
                if (choice == "C") {
                    for (auto it = customer1.begin(); it != customer1.end(); it++) {
                        if (it->getConsumeNum() == example.getNum()) {
                            it = customer1.erase(it);
                            break;
                        }
                    }
                    for (auto it = customer.begin(); it != customer.end(); it++) {
                        if (example.getNum() == (*it).getNum()) {
                            it = customer.erase(it);
                            break;
                        }
                    }
                }
                if (choice == "D") {
                    bool sign = false;
                    for (vector<ShopCar>::iterator it = customer1.begin(); it != customer1.end(); it++) {
                        if (example.getNum() == it->getConsumeNum()) {
                            sign = true;
                            for (vector<ShopLinked>::iterator it1 = customer2.begin(); it1 != customer2.end(); it1++) {
                                if (it->getShopCarNum() == it1->getStream()) {
                                    cout << *it1 << endl;
                                }
                            }
                        }
                    }
                    if (sign == false) {
                        cout << "此用户无购物车商品" << endl;
                    }
                }
                else {
                    cout << "输入非法" << endl;
                }
            }
            else {
                cout << "查无此人" << endl;
                cout << "是否加入此顾客（输入“是”或“否”）？" << endl;
                string str;
                cin >> str;
                if (str == "是") {
                    customer.push_back(example);
                }
                else {
            
                }
            }
            file.open("customers.txt", ios::out);
            for (auto it = customer.begin(); it != customer.end(); it++) {
                file << *it << endl;
            }
            file.close();
            file.open("ShopCarAll.txt", ios::out);
            for (auto it = customer1.begin(); it != customer1.end(); it++) {
                file << *it;
            }
            file.close();
            customer1.clear();
            customer2.clear();
        }
        else if (str == "B") { //商品操作

            cout << "商品信息如下：" << endl;
            vector<Goods> goods;
            Goods temp1;
            file.open("goods.txt", ios::in);
            while (file >> temp1) {
                goods.push_back(temp1);
            }
            file.close();
            for (auto p : goods) {
                showgoods(p);
            }
            cout << "请输入您希望进行的操作:\nA:录入新商品\nB:删除商品\nC:查询商品信息\nD:修改商品信息" << endl;
            cin >> op;

            if (op == "A") {
                cout << "请按编号、名称、价格、库存量、分类、上架时间,依次输入商品信息" << endl;
                Goods temp;
                cin >> temp;
                file.open("goods.txt", ios::app);
                file << endl;
                file << temp << endl;
                cout << "已完成添加" << endl;
                file.close();
            }
            else if (op == "B") {
                vector<Goods> goods;
                Goods temp;
                file.open("goods.txt", ios::in);
                while (file >> temp) {
                    goods.push_back(temp);
                }
                file.close();
                cout << "请输入想要删除的商品编号:";
                string removeId;
                cin >> removeId;
                cout << endl;
                bool flag = false;
                vector<Goods> midTemp;          //临时存放一下被删除的商品（修改点5）
                for (auto it = goods.begin(); it != goods.end(); ++it) {
                    if (it->getId() == removeId) {  // 直接通过 getId() 判断
                        Goods temp = *it;
                        midTemp.push_back(temp);
                        goods.erase(it);   // erase掉
                        flag = true;
                        break;
                    }
                    else {
                        continue;  // 不匹配，继续下一个元素
                    }
                }
                if (!flag) {
                    cout << "不存在待删除商品" << endl;
                }
                for (vector<Goods>::iterator it = midTemp.begin(); it != midTemp.end(); it++) {
                    cout << *it << endl;
                    ComDec(customer1, customer2, *it);
                }
                //覆盖文件
                file.open("customers.txt", ios::out);
                for (auto it = customer.begin(); it != customer.end(); it++) {
                    file << *it << endl;
                }
                file.close();
                file.open("ShopCarAll.txt", ios::out);
                for (auto it = customer1.begin(); it != customer1.end(); it++) {
                    file << *it;
                }
                file.close();
                file.open("goods.txt", ios::out);
                for (auto p : goods) {
                    file << p << endl;
                }
                file.close();
                cout << "商品删除成功" << endl;
                customer1.clear();
                customer2.clear();
            }
            else if (op == "C") {
                cout << "请输入想要查询商品编号:";
                string searchId;
                cin >> searchId;
                cout << endl;

                vector<Goods> goods;
                Goods temp;
                file.open("goods.txt", ios::in);
                while (file >> temp) {
                    goods.push_back(temp);
                }
                file.close();
                bool flag = false;
                for (auto it = goods.begin(); it != goods.end(); ++it) {
                    if (it->getId() == searchId) {  // 直接通过 getId() 判断
                        cout << "商品名称: " << it->getName() << " 商品价格:" << it->getPrice() << " 商品库存：" << it->getNum() << " 商品录入时间" << it->getTime() << endl;
                        flag = true;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if (!flag) {
                    cout << "无该匹配项" << endl;
                }

            }
            else if (op == "D") {
                vector<Goods> goods;
                Goods temp;
                string changeId;
                cout << "请输入待改商品id:";
                cin >> changeId;
                cout << endl;
                file.open("goods.txt", ios::in);
                while (file >> temp) {
                    goods.push_back(temp);
                }
                file.close();
                bool flag = false;
                for (auto it = goods.begin(); it != goods.end(); ++it) {
                    if (it->getId() == changeId) {  // 直接通过 getId() 判断
                        cout << "商品名称: " << it->getName() << " 商品价格:" << it->getPrice() << " 商品库存：" << it->getNum() << " 商品录入时间" << it->getTime() << endl;
                        cout << "请输入您要修改的属性:A:商品编号\nB:商品名称\nC:商品价格\nD:商品库存" << endl;
                        string op1;
                        cin >> op1;
                        if (op1 == "A") {
                            string newId;
                            cout << "请输入新编号，格式为SPxxxx..." << endl;
                            cin >> newId;
                            it->setId(newId);
                        }
                        else if (op1 == "B") {
                            string newName;
                            cout << "请输如新名称" << endl;
                            cin >> newName;
                            it->setName(newName);
                        }
                        else if (op1 == "C") {
                            double newPrice;
                            cout << "请输入新价格" << endl;
                            cin >> newPrice;
                            it->setPrice(newPrice);
                        }
                        else if (op == "D") {
                            int  newNum;
                            cout << "请输入更新库存量" << endl;
                            cin >> newNum;
                            cout << "商品名称: " << it->getName() << " 商品价格:" << it->getPrice() << " 商品库存：" << it->getNum() << " 商品录入时间" << it->getTime() << endl;
                            cout << "请输入您要修改的属性:A:商品编号\nB:商品名称\nC:商品价格\nD:商品库存" << endl;
                            string op1;
                            cin >> op1;
                            if (op1 == "A") {
                                string newId;
                                cout << "请输入新编号，格式为SPxxxx..." << endl;
                                cin >> newId;
                                it->setId(newId);
                            }
                            else if (op1 == "B") {
                                string newName;
                                cout << "请输如新名称" << endl;
                                cin >> newName;
                                it->setName(newName);
                            }
                            else if (op1 == "C") {
                                double newPrice;
                                cout << "请输入新价格" << endl;
                                cin >> newPrice;
                                it->setPrice(newPrice);
                            }
                            else if (op == "D") {
                                int  newNum;
                                cout << "请输入更新库存量" << endl;
                                cin >> newNum;
                                it->setNum(newNum);
                            }
                            else {
                                cout << "输入无效字符" << endl;
                            }
                            cout << "更改完成" << endl;
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    file.open("goods.txt", ios::out);
                    for (auto p : goods) {
                        file << p << endl;
                    }
                    file.close();
                    if (!flag) {
                        cout << "无该匹配项" << endl;
                    }
                }
            }
        }

               else if (str == "C")
               { // 商品目录操作
                   file.open("Table.txt", ios::in);
                   vector<GoodsTable> Tables;
                   GoodsTable temp;
                   while (file >> temp)
                   {
                       Tables.push_back(temp);
                   }
                   file.close();
                   // 测试用，输出文本
                   for (auto it : Tables)
                   {
                       showgoodTables(it);
                   }
                   buildLink(Tables);
                   cout << "请输入您想要对目录做的操作:\nA:添加节点\nB:删除节点\nC:查询节点\nD:修改节点" << endl;
                   char op;
                   cin >> op;
                   if (cin.fail())
                   {
                       cin.clear();
                       cin.ignore(INT_MAX, '\n');
                       cout << "输入错误，请重新输入操作类型！" << endl;
                       return -1;
                   }
                   if (op == 'A')
                   {
                       Add(Tables, file);
                   }
                   else if (op == 'B')
                   {
                       Remove(Tables, file);
                   }
                   else if (op == 'C')
                   {
                       Search(Tables);
                   }
                   else if (op == 'D')
                   {
                       Change(Tables, file);
                   }
                   else
                   {
                       cout << "抱歉，" << op << "属于无效字符。" << endl;
                   }
    }
               else
               {
                   cout << "输入错误，请在A,B,C中选择" << endl;
    }
               system("pause");
               system("cls");
                cout << "\t\t\t\t\t网上购物系统祝您使用愉快" << endl;
                cout << "请输入你要操作的业务\nA:顾客\nB:商品\nC:商品分类目录\nD购物车\nE:购物车商品信息\nF:保存此次操作并退出" << endl;
                cin >> str;
        }
        cout << "使用已完成，期待下次使用" << endl;
        return 0;
        
    }
    
    











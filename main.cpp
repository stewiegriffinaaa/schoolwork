#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include <algorithm>
#include<unordered_map>
#include <windows.h>
#include"goods.h"
#include"goodsTable1.h"
//先读出所有文件到队列里面，文本文件储存方式应该是 xxx xx
using namespace std;
void showgoods(Goods& a);
void showgoodTables(GoodsTable& a);
bool SearchById(string id, Goods temp);/*注：这里面有多次读取文件操作，之后要试试能不能给他封装到一个函数中当作形参传进去，否则太消耗性能*/
bool SearchByName(string name, Goods temp);

int main() {
    cout << "\t\t\t\t\t网上购物系统祝您使用愉快" << endl;
    string str;
    fstream file;
    string op;
    cout << "\n请选择操作类型：\n";
    cout << "\tA: 顾客功能\tB: 商品管理\tC:商品分类目录管理 \tD: 购物车管理\tE: 退出系统" << endl;
    cout << "请输入选项（A/B/C/D/E）: ";
    cin >> str;
    while (str != "F") {
        if (str == "A") { //顾客操作
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
            } else if (op == "B") {/*删除还需要删除购物车类，和商品清单类商品未完成*/
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
                for (auto it = goods.begin(); it != goods.end(); ++it) {
                    if (it->getId() == removeId) {  // 直接通过 getId() 判断
                        goods.erase(it);   // erase掉
                        flag = true;
                        break;
                    } else {
                        continue;  // 不匹配，继续下一个元素
                    }
                }
                if (!flag) {
                    cout << "不存在待删除商品" << endl;
                }
                //覆盖文件
                file.open("goods.txt", ios::out);
                for (auto p : goods) {
                    file << p << endl;
                }
                file.close();
                cout << "商品删除成功" << endl;
            } else if (op == "C") {
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
                    } else {
                        continue;
                    }
                }
                if (!flag) {
                    cout << "无该匹配项" << endl;
                }

            } else if (op == "D") {
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
                        } else if (op1 == "B") {
                            string newName;
                            cout << "请输如新名称" << endl;
                            cin >> newName;
                            it->setName(newName);
                        } else if (op1 == "C") {
                            double newPrice;
                            cout << "请输入新价格" << endl;
                            cin >> newPrice;
                            it->setPrice(newPrice);
                        } else if (op == "D") {
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
                        } else if (op1 == "B") {
                            string newName;
                            cout << "请输如新名称" << endl;
                            cin >> newName;
                            it->setName(newName);
                        } else if (op1 == "C") {
                            double newPrice;
                            cout << "请输入新价格" << endl;
                            cin >> newPrice;
                            it->setPrice(newPrice);
                        } else if (op == "D") {
                            int  newNum;
                            cout << "请输入更新库存量" << endl;
                            cin >> newNum;
                            it->setNum(newNum);
                        }
                        cout << "更改完成" << endl;
                        break;
                    } else {
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


        else if (str == "C") { //商品目录操作
            file.open("Table.txt", ios::in);
            vector<GoodsTable>Tables;
            GoodsTable temp;
            while (file >> temp) {
                Tables.push_back(temp);
            }
            file.close();
            //测试用，输出文本
            for (auto it : Tables) {
                showgoodTables(it);
            }
            for (auto it:Tables) {
                vector<string>childrenId = split(it.getChildrenId(), ',');
                if (childrenId.size() == 0) {
                    continue;
                }
                for (auto it1:Tables) { //防止乱序存储
//                cout<<"这里梅卡斯2"<<endl;
                    for (auto str : childrenId) {
                        if (str == it1.getId()) {
//                            cout<<"这里梅卡斯"<<endl;
                            GoodsTable* temp1 = &it1;
                            it.addChild(temp1);
                        }
                    }
                }
            }
            cout << "请输入您想要对目录做的操作:\nA:添加节点\nB:删除节点\nC:查询节点\nD:修改节点" << endl;
            string op;
            cin >> op;
            if (op == "A") {
                string newID;
                cout << "请输入父目录ID ";
                cin >> newID;
                cout << endl;
                bool flag = false;
                for (auto it : Tables) {
                    if (it.getId() == newID) {
                        flag = true;
                        
                        cout << "请按照新增目录ID,姓名，目录等级（父级目录加1），补充说明，创建时间(默认子节点数量为0，如需添加，请依次添加目录)" << endl;
                        string newId,newName,newAddition,newTime;
                        int newLevel;
                        cin >> newId>>newName>>newLevel>>newAddition>>newTime;
                        //string id, string name, int level, string addition,string time
                        GoodsTable temp(newId,newName,newLevel,newAddition,newTime);
                        it.addChild(&temp);
                        Tables.push_back(temp);
                        break;
                    }
                }
                if (!flag) {
                    cout << "未找到上级目录" << endl;
                }
                file.open("Table.txt", ios::out);
                //写入文件
                for (auto it : Tables) {
                    cout<<it;
                    file << it;
                }
                file.close();
            } else if (op == "B") {
                cout << "请输入要删除目录ID" << endl;
                string RemoveId;
                cin >> RemoveId;
                bool flag = false;
                for (auto it : Tables) {
                    if (it.getId() == RemoveId) {
                        flag = true;
                        //寻找父节点；
                        GoodsTable* par = it.getParent();
                        par->removeChild(&it);
                        //覆盖文件
                        file.open("Table.txt", ios::out);
                        //写入文件
                        for (auto it : Tables) {
                            file << it;
                        }
                        file.close();
                        cout << "删除完成" << endl;
                        break;
                    }
                }
                if (!flag) {
                    cout << "未找到该目录" << endl;
                }
            } else if (op == "C") {
                cout << "请输入您想查询的目录id" << endl;
                bool flag;
                string SearchId;
                cin >> SearchId;
                for (auto it : Tables) {
                    if (it.getId() == SearchId) {
                        cout << "该目录名称为" << it.getName() << ",有" << it.getNum() << "个子目录" << ",子目录ID为" << it.getChildrenId() << endl;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    cout << "未找到该目录" << endl;
                }
            } else if (op == "D") {
                //可修改分析：name,位置,补充说明
                string ChangeId;
                cout << "请输入待修改目录ID";
                cin >> ChangeId;
                cout << endl;
                bool flag = false;
                for (auto it : Tables) {
                    if (it.getId() == ChangeId) {
                        flag = true;
                        string op2;
                        cout << "请输入待修改属性:\tA:目录姓名\tB:补充说明\tC:目录位置:\t";
                        cin >> op2;
                        cout << endl;
                        if (op2 == "A") {
                            string newName;
                            cout << "请输入新名字:";
                            cin >> newName;
                            cout << endl;
                            it.setName(newName);
                            break;
                        } else if (op2 == "B") {
                            string newAddition;
                            cout << "请输入新说明:";
                            cin >> newAddition;
                            cout << endl;
                            it.setName(newAddition);
                        } else if (op2 == "C") {
                            string newParentId;
                            bool newflag = false;
                            cout << "请输入新父目录ID:";
                            cin >> newParentId;
                            cout << endl;
                            for (auto newpar : Tables) {
                                if (newpar.getId() == newParentId) {
                                    newflag = true;
                                    GoodsTable* t = it.getParent();
                                    t->removeChild(&(it));
                                    newpar.addChild(&(it));
                                    break;
                                }
                            }
                            if (!newflag) {
                                cout << "未找到该新父级目录" << endl;
                            }
                        }
                    }
                    if (!flag) {
                        cout << "未找到该目录" << endl;
                    } else {
                        file.open("Table.txt", ios::out);
                        //写入文件
                        for (auto it : Tables) {
                            file << it;
                        }
                        file.close();
                        cout << "修改完成" << endl;
                    }
                }
            }

        }




        else if (str == "D") { //对购物车的操作

        }

        else if (str == "E") { //对购物车商品清单进行操作


        }



        cout << "请输出你要操作的业务\nA:顾客\nB:商品\nC:购物车\nD购物车商品信息\nE:商品分类目录\nF:保存此次操作并退出" << endl;
        cin >> str;
    }
    cout << "使用已完成，期待下次使用" << endl;
    return 0;
}

void showgoods(Goods & a) {
    cout << "商品名称" << a.getName() << " 商品编号" << a.getId() << " 商品价格" << a.getPrice() << " 商品库存" << a.getNum() << " 商品上架时间" << a.getTime() << endl;
}
void showgoodTables(GoodsTable& a) {
    cout << "目录名称" << a.getName() << " 目录编号" << a.getId() << " 目录子节点等级" << a.getLevel() << " 子目录数量" << a.getNum() << " 目录时间" << a.getTime() << endl;
}














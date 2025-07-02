#pragma once
#include"goods.h"
#include"ShopCar.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Node
{
//public:
    Goods type;
    int count;
    Node* dire;
public:
    Node() {
        this->count = 0;
        this->dire = NULL;
    }
    Node(Goods type, int num){
        this->type = type;
        this->count = num;
        this->dire = NULL;
    }
    friend class ShopLinked;
    friend ostream& operator<<(ostream& out, ShopLinked& example);
};
class ShopLinked
{
    string StreamDate;
    string signal;
    double sum;
    Node head;
public:
    ShopLinked(ShopCar& example) {
        StreamDate = example.getShopCarNum();
        signal = example.getShopCarNum();
        StreamDate = example.getShopCarNum();
        this->sum = 0;
        for (vector<Goods>::iterator it = example.getNum().begin(); it != example.getNum().end(); it++) {
            this->Insert(*it, 1);
    //        cout << *it << endl; //wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
            sum += (*it).getPrice();
        }
    }
    ShopLinked(const ShopLinked& example) {
        StreamDate = example.StreamDate;
        signal = example.StreamDate;
        StreamDate = example.StreamDate;
        this->sum = example.sum;
        Node* p = &this->head;
        const Node*q = &example.head;
        while (q->dire != NULL) {
            Node* m = new Node(q->dire->type, q->dire->count);
            p->dire = m;
            p->dire->dire = NULL;
            p = p->dire;
            q = q->dire;
        }
    }
    void setSum() {
        sum = 0;
        Node* p = head.dire;
        while (p->dire != NULL) {
            sum += p->count * p->type.getPrice();
            p = p->dire;
        }
        sum += p->count * p->type.getPrice();
    }
    void Insert(Goods ty, int num) {
    //    cout << this->getStream() << endl;
        Node* p = &head;
        bool aw = 1;
        while (p->dire != NULL) {
            if (p->dire->type.getName() == ty.getName()) {
                p->dire->count += num;
                aw = 0;
     //           cout << "已添加：" << p->dire->type <<  p->dire->count << endl;//wwwwwwwwwwwwwwwwwwww
                break;
            }
            p = p->dire;
        }
        if (aw) {
            Node* mid = new Node(ty, num);
            p->dire = mid;
    //        cout << "已添加www" << p->dire->type << endl;
            p->dire->dire = NULL;
        }
    }
    bool is_empty() {
        if (head.dire == NULL)
            return 1;
        return 0;
    }
    bool pop(Goods ty, int num) {
        Node* p = &head;
        if (this->is_empty() == 1)
            return 0;
        while (p->dire->dire != NULL) {
            if (p->dire->type.getId() == ty.getId()) {
                if (p->dire->count > num) {
                    p->dire->count -= num;
                    return 1;
                }
                if (p->dire->count == num) {
                    Node* q = p->dire->dire;
                    delete p->dire;
                    p->dire = q;
                    return 1;
                }
            }
            p = p->dire;
        }
        if (p->dire->type.getId() == ty.getId()) {
            if (p->dire->count > num) {
                p->dire->count -= num;
                return 1;
            }
            if (p->dire->count == num) {
                delete p->dire;
                p->dire = NULL;
                return 1;
            }
        }
        return 0;
    }
    bool popTail() {
        Node* p = &head;
        if (this->is_empty())
            return 1;
        while (p->dire->dire != NULL) {
            p = p->dire;
        }
        delete p->dire;
        p->dire = NULL;
        return 0;
    }
    bool CompleteDec(Goods ty) {
        if (is_empty()) return false;  // 空链表直接返回

        Node* p = &head;
        bool deleted = false;

        // 遍历链表寻找匹配节点
        while (p->dire != NULL) {  // 正确循环条件：检查下一个节点是否存在
            if (p->dire->type.getId() == ty.getId()) {
                Node* temp = p->dire;  // 保存待删除节点
                p->dire = temp->dire;  // 重新连接链表
                delete temp;  // 释放内存
                deleted = true;
                // 不移动指针，继续检查当前位置（可能有多个相同节点）
            }
            else {
                p = p->dire;  // 未找到匹配节点，移动指针
            }
        }

        // 更新总金额（如果有商品被删除）
        if (deleted) {
            setSum();  // 假设setSum()用于重新计算总金额
        }

        return deleted;  // 返回是否成功删除节点
    }
    string getStream() {
        return this->StreamDate;
    }
    ~ShopLinked() {
        while (this->is_empty() == 0) {
            this->popTail();
        }
    }
    friend ostream& operator<<(ostream& out, ShopLinked& example);
 //   Node& getHead() {
 //       return head;  //wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
 //   }
};
ostream& operator<<(ostream& out, ShopLinked& example) {
    Node* p = example.head.dire;
    out << "统计内容: " << endl;
    out << "流水号：" << example.StreamDate << " 购物车编号: " << example.signal << " 总共应付款：" << example.sum << endl;
    while (p != NULL) {
        out << p->type << " 总计：" << p->count << " 个" << endl;
        p = p->dire;
    }
    return out;
}

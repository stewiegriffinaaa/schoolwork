#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include <algorithm>
#include <sstream>
using namespace std;


//一个字符串分割函数
vector<string> split(string str, char t) {
	vector<string> result;
	if (str.empty()) {
		return result;
	}
	istringstream iss(str);//空字符串流；
	string token;//临时储存
	while (getline(iss, token, t)) {
		if (!token.empty()) {
			result.push_back(token);
		}
	}
	return result;
}

//拼接字符串
string strcat(vector<string> a) {
	string result = *a.begin();//先将第一段拼上
	for (auto it = a.begin()++; it != a.end(); ++it) { //从第二个来时
		result += "," + *it;//依次拼接
	}
	return result;
}




class GoodsTable {
	string type = "goodsTable";
	string id;
	string name;
	int level;//等级
	string addition;//补充说明
	string time;//添加时间xxxx-xx-xx
	GoodsTable* parent = nullptr;//父节点
	int num;//子节点数量
	string chindrenId;//子节点ID,以ID1,ID2,ID3...形式存储与读取
	vector<GoodsTable*> children;//存储子节点
public:
	GoodsTable(string id, string name, int level, string addition, int num, string Children) {
		this->id = id;
		this->name = name;
		this->level = level;
		this->addition = addition;
		this->num = num;
		this->chindrenId = Children;
		//			this->pid = pid;
	}


	~GoodsTable() {};
	GoodsTable() {};

	friend istream& operator>>(istream& in, GoodsTable& obj) {//从文件中读
		in >> obj.id >> obj.name >> obj.level >> obj.addition >> obj.time >> obj.num >> obj.chindrenId;
		return in;
	}
	friend ostream& operator<<(ostream& out, GoodsTable& obj) {
		out << obj.id << " " << obj.name << " " << obj.level << " " << obj.addition << " " << obj.time << " " << obj.num << " " << obj.chindrenId << endl;
		return out;
	}


	//属性接口
	string getType() const {
		return type;
	}
	string getId() const {
		return id;
	}
	string getName() const {
		return name;
	}
	int getLevel() const {
		return level;
	}
	string getAddition() const {
		return addition;
	}
	string getTime() const {
		return time;
	}
	GoodsTable* getParent() const {
		return parent;
	}
	int getNum() const {
		return num;
	}
	string getChildrenId() const {
		return chindrenId;
	}
	vector<GoodsTable*> getChildren() const {
		return children;
	}


	void setId(string id) {
		this->id = id;
	}
	void setName(string name) {
		this->name = name;
	}
	void setLevel(int level) {
		this->level = level;
	}
	void setAddition(string addition) {
		this->addition = addition;
	}
	void getTime(string time) {
		this->time = time;
	}
	void setNum(int num) {
		this->num = num;
	}




	void setParent(GoodsTable* p) {
		parent = p;
		if (p) p->addChild(this);
	}


	void addChild(GoodsTable* child) {
		children.push_back(child);
		child->setLevel(this->level - 1);
		child->setParent(this);
		this->num++;
		this->chindrenId = this->chindrenId + "," + child->id;
	}




	void removeChild(GoodsTable* child) {
		auto it = find(children.begin(), children.end(), child);
		if (it != children.end()) {
			children.erase(it);
			this->num--;
			vector<string> result = split(this->chindrenId, ',');
			auto it1 = find(result.begin(), result.end(), child->getId());
			result.erase(it1);
			this->chindrenId = strcat(result);
		}
		else {
			cout << "没有该目录" << endl;
		}
	}


	GoodsTable* findChildById(const string& childId) const {
		for (auto child : children) {
			if (child->getId() == childId) {
				return child;
			}
		}
		return nullptr;
	}


};

#pragma once
#include<iostream>
#include"goodsTable1.h"
#include <limits>
#include<fstream>
#include<unordered_map>
#include <climits>
void Add(vector<GoodsTable>& Tables, fstream& file) {
	string newID;
	cout << "请输入父目录ID ";
	cin >> newID;
	cout << endl;
	bool flag = false;
	for (auto& it : Tables) {
		if (it.getId() == newID) {
			flag = true;
			cout << "请按照新增目录ID,姓名，补充说明，创建时间(默认子节点数量为0，如需添加，请依次添加目录)" << endl;
			string newId, newName, newAddition, newTime;
			cin >> newId >> newName >> newAddition >> newTime;
			GoodsTable* temp = new GoodsTable(newId, newName, it.getLevel() + 1, newAddition, newTime);
			it.addChild(temp);
			cout << it << endl;
			Tables.push_back(*temp);
			break;
		}
	}
	if (!flag) {
		cout << "未找到上级目录" << endl;
	}
	file.open("Table.txt", ios::out);
	for (auto it : Tables) { // 注意：这里存储的是对象副本，若GoodsTable含指针需调整（原问题1）
		file << it;
	}
	file.close();
}
void Remove(vector<GoodsTable>& Tables, fstream& file) {
	cout << "请输入要删除目录ID" << endl;
	string RemoveId;
	cin >> RemoveId;
	bool flag = false;
	if (RemoveId != "ML0000") {
		for (auto& it : Tables) { // 已改为引用遍历
			if (it.getId() == RemoveId) {
				flag = true;
				GoodsTable* par = it.getParent();
				if (par) { // 新增空指针检查
			//		cout << "目录名字" << it.getName() << endl;
					par->removeChild(&it, Tables);
				}
				file.open("Table.txt", ios::out);
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
	}
	else {
		cout << "不能删除根目录" << endl;
	}
}
void Search(vector<GoodsTable>& Tables) {
	cout << "请输入您想查询的目录id" << endl;
	string SearchId;
	cin >> SearchId;
	bool flag = false; // 修正变量作用域（原问题2）
	for (auto& it : Tables) { // 已改为引用遍历（原问题1）
		if (it.getId() == SearchId) {
			cout << "该目录名称为" << it.getName() << ",有" << it.getNum() << "个子目录" << ",子目录ID为" << it.getChildrenId() << endl;
			flag = true;
			// 移除无效的cout<<"已查询"<<num<<"次"<<endl;（原问题2）
			break;
		}
	}
	if (!flag) {
		cout << "未找到该目录" << endl;
	}
}
void Change(vector<GoodsTable>& Tables, fstream& file) {
	string ChangeId;
	cout << "请输入待修改目录ID: ";
	cin >> ChangeId;
	cout << endl;
	bool flag = false;
	for (auto& it : Tables) {
		if (it.getId() == ChangeId) {
			flag = true;
			string op2;
			cout << "请输入待修改属性(A:姓名 B:补充说明 C:父目录): ";
			cin >> op2;
			cout << endl;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "输入错误，请重新输入属性！" << endl;
				continue;
			}

			if (op2 == "A") {
				string newName;
				cin >> newName;
				it.setName(newName);
			}
			else if (op2 == "B") {
				string newAddition;
				cin >> newAddition;
				it.setAddition(newAddition);
			}
			else if (op2 == "C") {
				string newParentId;
				cin >> newParentId;
				cout << endl;

				// 查找新父目录（引用遍历原对象）
				GoodsTable* newPar = nullptr;
				for (auto& par : Tables) { //引用遍历
					if (par.getId() == newParentId) {
						newPar = &par;
						break;
					}
				}
				if (newPar) {
					// 获取原父目录并移除当前节点
					GoodsTable* oldPar = it.getParent();
					if (oldPar) {
						oldPar->removeChild(&it, Tables); // 从原父目录移除
					}
					newPar->addChild(&it); // 添加到新父目录
					cout << "未找到新父目录！" << endl;
				}
				else {
				}
			}
			else {
				cout << "op ==== end" << endl;
			}
		}
		break; // 找到目标后退出循环
	}
	if (!flag) {
		cout << "未找到该目录！" << endl;
	}
	else {
		file.open("Table.txt", ios::out);
		for (const auto& it : Tables) { // 使用const引用避免拷贝
			file << it;
		}
		file.close();
		cout << "修改完成！" << endl;
		//		break;
	}
}
void buildLink(vector<GoodsTable>& Tables) {
	for (auto& it : Tables) {
		vector<string>childrenId = split(it.getChildrenId(), ',');
		if (childrenId.size() == 0) {
			continue;
		}
		for (auto& it1 : Tables) { // 防止乱序存储
			for (auto str : childrenId) {
				if (str == it1.getId()) {
					GoodsTable* temp1 = &it1;
					it.reBuild(temp1);
				}
			}
		}
	}
}

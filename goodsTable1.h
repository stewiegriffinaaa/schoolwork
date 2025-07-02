#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <sstream>
using namespace std;

// 一个字符串分割函数
vector<string> split(string str, char t)
{
    vector<string> result;
    if (str.empty())
    {
        return result;
    }
    istringstream iss(str); // 空字符串流；
    string token;           // 临时储存
    while (getline(iss, token, t))
    {
        if (!token.empty())
        {
            result.push_back(token);
        }
    }
    return result;
}

// 拼接字符串
string strcat(vector<string> a)
{
    string result = *a.begin(); // 先将第一段拼上
    for (auto it = a.begin()++; it != a.end(); ++it)
    {                      // 从第二个来时
        result += "," + *it; // 依次拼接
    }
    return result;
}

class GoodsTable
{
    string type = "goodsTable";
    string id;                     // 不可更改
    string name;                   // 可更改
    int level;                     // 等级 不可单独更改（必须指明新的父节点）
    string addition;               // 补充说明 可更改
    string time;                   // 添加时间xxxx-xx-xx 可更改，但没必要
    GoodsTable* parent = nullptr;  // 父节点
    int num;                       // 子节点数量
    string childrenId;             // 子节点ID,以ID1,ID2,ID3...形式存储与读取
    vector<GoodsTable*> children; // 存储子节点
    void setLevel(int n)
    {
        this->level = n;
    }

public:
    GoodsTable(string id, string name, int level, string addition, string time)
    {
        this->id = id;
        this->name = name;
        this->level = level;
        this->addition = addition;
        this->num = 0;
        this->childrenId = "";
        this->time = time;
        //			this->pid = pid;
    }

    ~GoodsTable() {}

    GoodsTable() {};
    friend istream& operator>>(istream& in, GoodsTable& obj)
    {
        string line;
        if (!getline(in, line))
        { // 读取整行
            return in;
        }
        vector<string> style = split(line, ' ');
        obj.id = style[0];
        obj.name = style[1];
        obj.level = stoi(style[2]);
        obj.addition = style[3];
        obj.time = style[4];
        obj.num = stoi(style[5]);
        if (style.size() == 7)
        {
            obj.childrenId = style[6];
        }
        else if (style.size() == 6)
        {
            obj.childrenId = "";
        }
        else
        {
            return in;
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const GoodsTable& obj)
    {
        if (obj.childrenId != "")
        {
            out << obj.id << " " << obj.name << " " << obj.level << " " << obj.addition << " " << obj.time << " " << obj.num << " " << obj.childrenId << endl;
        }
        else
        {
            out << obj.id << " " << obj.name << " " << obj.level << " " << obj.addition << " " << obj.time << " " << obj.num << endl;
        }

        return out;
    }
    bool operator==(GoodsTable& temp)
    {
        bool flag = true;
        if (temp.getId() != this->getId())
        {
            return false;
        }

        return flag;
    }

    // 属性接口
    string getType() const
    {
        return type;
    }
    string getId() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    int getLevel() const
    {
        return level;
    }
    string getAddition() const
    {
        return addition;
    }
    string getTime() const
    {
        return time;
    }
    GoodsTable* getParent() const
    {
        return parent;
    }
    int getNum() const
    {
        return num;
    }
    string getChildrenId() const
    {
        return childrenId;
    }
    vector<GoodsTable*> getChildren()
    {
        return children;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setAddition(string addition)
    {
        this->addition = addition;
    }
    void getTime(string time)
    {
        this->time = time;
    }
    void setNum(int num)
    {
        this->num = num;
    }

    void setParent(GoodsTable* p)
    {
        parent = p;
    }

    void reBuild(GoodsTable* child)
    {
        child->setLevel(this->level + 1);
        child->setParent(this);
        children.push_back(child);
    }
    void addChild(GoodsTable* child)
    {
        children.push_back(child);
        child->setLevel(this->level + 1);
        child->setParent(this);
        this->num++;
        if (this->childrenId[0] != 'M')
        {
            this->childrenId = child->id;
        }
        else
        {
            this->childrenId = this->childrenId + "," + child->id;
        }
    }
    void removeChild(GoodsTable* child, vector<GoodsTable>& t)
    {
        // 1. 更新num
        setNum(--this->num);
        // 2. 重建childrenId
        vector<string> childIds = split(childrenId, ',');
        auto it1 = find(childIds.begin(), childIds.end(), child->getId());
        if (it1 != childIds.end())
        {
            childIds.erase(it1);
        }
        // 重新生成childrenId字符串
        childrenId = "";
        for (size_t i = 0; i < childIds.size(); ++i)
        {
            if (!childrenId.empty())
                childrenId += ",";
            childrenId += childIds[i];
        }
        child->removeAllChild(t);
        cout << "子节点已移除，当前子节点数量：" << this->num << endl;
        return;
    }

    //		void removeAllChild(vector<GoodsTable>& t) {
    //			// 1. 递归删除子节点（从底层向上）
    //			for (auto it = children.rbegin(); it != children.rend(); ++it) {
    //				(*it)->removeAllChild(t);
    //			}
    //			// 2. 清理当前节点的子节点列表
    //			children.clear();
    //			childrenId = "";
    //			num = 0;
    //			// 3. 从父容器中移除自己（反向遍历避免失效）
    //			for (auto it = t.rbegin(); it != t.rend(); ++it) {
    //				if (*it == *this) {
    //					t.erase((it + 1).base()); // 转换为正向迭代器后删除
    //					break;
    //				}
    //			}
    //		}
    void removeAllChild(vector<GoodsTable>& t)
    {
        // 收集所有需要删除的节点ID（包括自己和所有后代节点）
        vector<string> toDelete;
        collectAllDescendants(this->id, t, toDelete);

        // 从vector中删除所有收集到的节点
        for (const string& deleteId : toDelete)
        {
            for (auto it = t.begin(); it != t.end(); ++it)
            {
                if (it->getId() == deleteId)
                {
                    t.erase(it);
                    break;
                }
            }
        }
    }

    // 静态辅助函数：递归收集指定节点及其所有后代节点的ID
    static void collectAllDescendants(const string& nodeId, vector<GoodsTable>& allNodes, vector<string>& result)
    {
        // 添加当前节点ID到删除列表
        result.push_back(nodeId);

        // 找到当前节点
        for (auto& node : allNodes)
        {
            if (node.getId() == nodeId)
            {
                // 如果有子节点，递归处理每个子节点
                if (!node.getChildrenId().empty())
                {
                    vector<string> childIds = split(node.getChildrenId(), ',');
                    for (const string& childId : childIds)
                    {
                        // 递归收集每个子节点及其后代
                        collectAllDescendants(childId, allNodes, result);
                    }
                }
                break;
            }
        }
    }
};

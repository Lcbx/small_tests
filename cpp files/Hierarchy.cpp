#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cassert>

#include <chrono>
#include <utility>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F, typename... Args>
double funcTime(F func, Args&&... args) {
	TimeVar t1 = timeNow();
	func(std::forward<Args>(args)...);
	return duration(timeNow() - t1);
}

#undef duration
#undef timeNow



class AbstractNode {
public:
	std::string Name;

	virtual AbstractNode& getParent() {
		throw "not implemented";
	}

	virtual void setParent(AbstractNode& parent) {
		throw "not implemented";
	}

	virtual void addChild(AbstractNode& child) {
		throw "not implemented";
	}

	virtual bool hasChildren() {
		throw "not implemented";
	}
	
	// seems that std::vector<AbstractNode&> is compiler-unfriendly
	virtual std::vector<AbstractNode*> getChildren() {
		throw "not implemented";
	}

	virtual AbstractNode& getFirstChild() {
		throw "not implemented";
	}

	int countNodes() {
		int total = 1;
		for each (AbstractNode* child in getChildren())
		{
			total += child->countNodes();
		}
		return total;
	}

	static std::string prettyName(std::string name) {
		return std::string(7 - name.length(), '-') + name;
	}

	std::string printTree(int level = 0){

		auto repr = prettyName(Name);
		if (level > 0) {
			repr = std::string((level - 1) * 8, ' ') + "    |--" + repr;
		}

		AbstractNode* current = this;
		int exploredLevel = level;

		while(current->hasChildren()){
			AbstractNode& firstChild = current->getFirstChild();
			exploredLevel += 1;
			repr += "-" + prettyName(firstChild.Name);
			current = &firstChild;
		}
		
		repr += "\n";

		while (exploredLevel!=level) {
			current = &current->getParent();
			exploredLevel -= 1;
			repr += current->_endPrintTree(exploredLevel);
		}
		return repr;
	}
	std::string _endPrintTree(int level) {
		std::string repr = "";
		auto children = getChildren();
		auto it = children.begin();
		it++;
		while (it != children.end())
		{
			repr += (*it)->printTree(level +1);
			it++;
		}
		return repr;
	}
};


class NaiveNode : public AbstractNode {
	AbstractNode* Parent = nullptr;
	std::vector<AbstractNode*> Children = std::vector<AbstractNode*>();
public:

	virtual AbstractNode& getParent() {
		return *Parent;
	}

	virtual void setParent(AbstractNode& parent) {
		if(Parent!=&parent){
			Parent = &parent;
			parent.addChild(*this);
		}
	}

	virtual void addChild(AbstractNode& child) {
		child.setParent(*this);
		if(&child != this && std::find(Children.begin(), Children.end(), &child) == Children.end()){
			Children.push_back(&child);
		}
	}

	virtual bool hasChildren() {
		return Children.size() != 0;
	}

	virtual std::vector<AbstractNode*> getChildren() {
		return Children;
	}

	virtual AbstractNode& getFirstChild() {
		return *Children[0];
	}
};


class MyNode : public AbstractNode {
	static std::map<int, MyNode*> Tree;
	int Hash = -1;
	int nChildren = 0;
public:

	virtual MyNode& getParent() {
		return *Tree[(Hash - 1) / 2];
	}

	virtual void setParent(MyNode& parent) {
		// Tree = parent.Tree;
		if (&parent == this) {
			Hash = 0;
		}
		else if (!parent.hasChildren()) {
			Hash = parent.Hash * 2 + 1;
			parent.nChildren += 1;
		}
		else {
			int n = parent.nChildren;
			Hash = (parent.Hash+1) * pow(2, n+1) + pow(2, n) -2;
			parent.nChildren += 1;
		}
		Tree[Hash] = this;
	}

	virtual void addChild(MyNode& child) {
		child.setParent(*this);
	}

	virtual std::vector<AbstractNode*> getChildren() {
		if (hasChildren()) {
			auto result = std::vector<AbstractNode*>();
			MyNode* current = &getFirstChild();
			result.push_back(current);
			while (current->hasSibling()){
				auto sibling = &current->getSibling();
				result.push_back(sibling);
				current = sibling;
			}
			return result;
		}
		return std::vector<AbstractNode*>();
	}

	virtual bool hasChildren() {
		return nChildren != 0;
	}

	virtual MyNode& getFirstChild() {
		return *Tree[Hash * 2 + 1];
	}

	virtual bool hasSibling() {
		return Tree.count(Hash * 2 + 2);
	}

	virtual MyNode& getSibling() {
		return *Tree[Hash * 2 + 2];
	}
};
std::map<int, MyNode*> MyNode::Tree = std::map<int, MyNode*>();


template<typename T>
std::vector<T> generateTree(int size) {
	std::srand(42);
	auto vector = std::vector<T>(size);

	T& root = vector[0];
	root.Name = "Root";
	root.setParent(root);

	for (int i = 1; i < size; i++) {
		T& node = vector[i];
		node.Name = "node" + std::to_string(i);

		int parentIndex = std::rand() % i;
		T& parent = vector[parentIndex];
		node.setParent(parent);
#if false
		std::cout << node.Name << " parent is " << parent.Name << std::endl;
		for each (auto child in parent.getChildren())
		{
			std::cout << child->Name << ", ";
		}
		std::cout << std::endl;
#endif
	}
	assert(root.countNodes() == size);
	return vector;
}

template<typename T>
std::vector<T> testTree(int size) {
	std::srand(113);
	

}


int main() {

	static auto naive = generateTree<NaiveNode>(1000);
	//std::cout << naive[0].printTree();

	static auto mine = generateTree<MyNode>(1000);
	//std::cout << mine[0].printTree();

	auto testN = [] { naive[0].printTree(); };
	auto testM = [] { mine[0].printTree(); };


	std::cout << "norm: " << funcTime(testN) << "\n";
	std::cout << "algo: " << funcTime(testM);


	int i;
	std::cin >> i;

	return 0;
}
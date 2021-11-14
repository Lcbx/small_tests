#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>


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

	void printTree(int level = 0){

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
		
		std::cout << repr << std::endl;

		while (exploredLevel!=level) {
			current = &current->getParent();
			exploredLevel -= 1;
			current->_endPrintTree(exploredLevel);
		}
	}
	void _endPrintTree(int level) {
		auto children = getChildren();
		auto it = children.begin();
		it++;
		while (it != children.end())
		{
			(*it)->printTree(level +1);
			it++;
		}
	}
};


class NaiveNode : public AbstractNode {
	AbstractNode* Parent;
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

int main() {

	auto naive = generateTree<NaiveNode>(10);
	naive[0].printTree();

	int i;
	std::cin >> i;

	return 0;
}
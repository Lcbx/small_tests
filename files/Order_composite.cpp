#pragma once
#include <iostream>
#include <list>
#include<memory>


using namespace std;

//classe mere des ordres
class Order{ public: virtual ~Order(){} virtual void execute()=0; };
//exemples d'ordres
class SayHello : public Order { public: void execute(){ cout << "hello\n"; } };
class SayHi : public Order { public: void execute(){ cout << "hi\n"; } };
class Composite : public Order, public list<unique_ptr<Order>> {
public:
	~Composite(){ for(auto it=begin(); it!=end();){ it->reset(); erase(it++); } }
	void execute(){
		for(auto it=begin(); it!=end();){
			(*it)->execute();
			it->reset();
			erase(it++);
		}
	}
};


//test
/*
int main(){
	Composite c;
	c.push_back( unique_ptr<Order>(new SayHi()) );
	c.push_back( unique_ptr<Order>(new SayHello()) );
	c.execute();
	return 0;
}
*/


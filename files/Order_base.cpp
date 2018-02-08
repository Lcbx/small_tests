#pragma once
#include <iostream>
#include <vector>
#include <memory>


using namespace std;

//classe mere des ordres
class Order{ public: virtual ~Order(){} virtual void execute()=0; };
//exemplesd'ordres
class SayHello : public Order { public: void execute(){ cout << "hello\n"; } };
class SayHi : public Order { public: void execute(){ cout << "hi\n"; } };

//la classe qui gere les ordres
class Commander : public vector<unique_ptr<Order>> {
public:
	void doSomething(){
		if( !empty() ) {
			back()->execute();
			back().reset();
			pop_back();
		}
		else cout << "no more commands\n";
	}
};

//test
/*
int main(){
	Commander com;
	com.push_back( unique_ptr<Order>(new SayHello()) );
	com.push_back( unique_ptr<Order>(new SayHi()) );
	com.doSomething();
	com.doSomething();
	com.doSomething();
	return 0;
}
*/

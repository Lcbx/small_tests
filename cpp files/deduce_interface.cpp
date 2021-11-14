#pragma once
#include <iostream>

class IMyInterface  // Inheritance from this is optional
{
public:
	virtual void MyMethod() = 0;
};

class MyClass  // Does not explicitly implement IMyInterface
{
public:
	void MyMethod()  // But contains a compatible method definition
	{
		std::cout << "Hello, world!\n";
	}
};

class MyOtherClass  // Does not explicitly implement IMyInterface
{
public:
	void MyMethod()  // But contains a compatible method definition
	{
		std::cout << "Hi, Bud\n";
	}
};

template<typename MyInterface>
void CallMyMethod(MyInterface& m)
{
	m.MyMethod();  // instantiation succeeds iff MyInterface has MyMethod
}

/*
int main() {

	MyClass obj;
	MyOtherClass o;

	CallMyMethod(obj);     // Automatically generate code with MyClass as 
	CallMyMethod(o);	   // MyInterface

	void** arr;
	arr = new void*[10];

	arr[0] = &obj;
	arr[1] = &o;

	CallMyMethod(*((MyClass*) arr[0]));
	CallMyMethod(*((MyOtherClass*)arr[1]));

	int i;
	std::cin >> i;

	return 0;
}
*/
#pragma once

#include <iostream>
#include <string>

#include <type_traits>
#include <initializer_list>

#include <map>
#include <vector>

struct signature {
	signature(int i, std::string s) : parameters(i), name(s) {}
	int parameters;
	std::string name;
};


struct Object {
	std::map<std::string, void*> functions;
};

void doSomething(Object& o) {
	std::cout << "hello\n";
}


void call(void* f) {
	auto func = (void(*)()) f;
	func();
}
void call(void* f, Object& o1) {
	auto func = (void(*)(Object&)) f;
	func(o1);
}
void call(void* f, Object& o1, Object& o2) {
	auto func = (void(*)(Object&, Object&)) f;
	func(o1, o2);
}


struct test : public Object {
	test() {
		functions["hello"] = &doSomething;
	}
};

/*
int main() {

	test t;
	call(t.functions["hello"], t);

	int i;
	std::cin >> i;

	return 0;
}
*/
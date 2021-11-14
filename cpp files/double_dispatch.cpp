
#include <iostream>

//double dispatch
class Parent {
public:
	Parent() {}
	virtual ~Parent() {}
};
class Son : public Parent {
public:
	void think() {
		std::cout << "i sometimes think, and then about important matters\n";
	}
};
class Daughter : public Parent {
public:
	void think() {
		std::cout << "i mostly think about trivial matters\n";
	}
};

void dispatchSS(Son& a, Son& b) {
	std::cout << "Son/Son\n";
	a.think();
	b.think();
}

void dispatchSD(Son& a, Daughter& b) {
	std::cout << "Son/Daughter\n";
	a.think();
	b.think();
}

void dispatchDD(Daughter& a, Daughter& b) {
	std::cout << "Daughter/Daughter\n";
	a.think();
	b.think();
}


void doSomethingSP(Son* s1, Parent* p2) {
	if (auto s2 = dynamic_cast<Son*>(p2)) dispatchSS(*s1, *s2);
	else if (auto d2 = dynamic_cast<Daughter*>(p2)) dispatchSD(*s1, *d2);
}
void doSomethingDP(Daughter* d1, Parent* p2) {
	if (auto s2 = dynamic_cast<Son*>(p2)) dispatchSD(*s2, *d1);
	else if (auto d2 = dynamic_cast<Daughter*>(p2)) dispatchDD(*d1, *d2);
}
void doSomething(Parent* p1, Parent* p2) {
	if (auto s1 = dynamic_cast<Son*>(p1)) doSomethingSP(s1, p2);
	else if (auto d1 = dynamic_cast<Daughter*>(p1)) doSomethingDP(d1, p2);
}




/*
int main() {

	Son Luc;
	Son Matthieu;
	Daughter Mad;

	doSomething((Parent*)&Luc, (Parent*)&Luc);
	doSomething((Parent*)&Luc, (Parent*)&Matthieu);

	doSomething((Parent*)&Luc, (Parent*)&Mad);
	doSomething((Parent*)&Mad, (Parent*)&Luc);
	doSomething((Parent*)&Matthieu, (Parent*)&Mad);


	doSomething((Parent*)&Mad, (Parent*)&Mad);

	int i;
	std::cin >> i;

	return 0;
}
*/
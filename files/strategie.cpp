#pragma once

#include<iostream>

using namespace std;


class Strategie {
public:
	virtual void doIt() = 0;
};


class StratHello : public Strategie {
public:
	virtual void doIt() { cout << "Hello\n"; }
};

class StratHi : public Strategie {
public:
	virtual void doIt() { cout << "Hi\n"; }
};

class Executer {
	Strategie* strat_ = nullptr;
	Executer(Strategie* strat) : strat_(strat) {}
	~Executer() { delete strat_; }
public:
	static Executer* obtenirInstance() {
		static Executer instance_(nullptr);
		return &instance_;
	}
	void setStrat(Strategie* strat) { delete strat_; strat_ = strat; }
	void execute() { if(strat_!=nullptr) strat_->doIt(); }
};

namespace C {
	extern void execute() { Executer::obtenirInstance()->execute(); }
	extern void setStrat(Strategie* strat) { Executer::obtenirInstance()->setStrat(strat); }
}

/*
int main(){
	C::setStrat(new StratHello);
	C::execute();
	C::setStrat(new StratHi);
	C::execute();

	int i;
	cin >> i;
}
*/
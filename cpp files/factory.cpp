#pragma once
#include <iostream>
#include <memory>
#include <map>


using namespace std;


//la classe mere
class Object { public: virtual void greeting(){ cout << "gah\n"; } };
//les classes a instancier
class Foo : public Object { public: void greeting() { cout << "hello\n"; } };
class Bar : public Object { public: void greeting() { cout << "hi\n"; } };

//la fabrique
class Factory {
	//patron singleton statique
	Factory();
	static Factory instance;
	//le log contenant l'associant string/constructeur
	map<string, unique_ptr<Object>(*)()> log;
	//la foncion de construction interne
	template<typename T> static unique_ptr<Object> instantiate() { return unique_ptr<Object>(new T); }
public:
	//permet de savoir si le nom est deja associe
	static bool existe(string nom) { return Factory::instance.log.find(nom)!=Factory::instance.log.end(); }
	//la fonction de construction externe
	static unique_ptr<Object> create(string nom) { return Factory::instance.log[nom](); }
};
Factory Factory::instance = Factory(); //instancie la classe dès l'initialisation
Factory::Factory(){
	//enregistrement des classes dans le constructeur
	#define REGISTER(nom) Factory::instance.log[#nom] = &Factory::instantiate<nom>
	
	
	REGISTER(Foo);
	REGISTER(Bar);
	
	
	#undef REGISTER
}


//test
/*
int main() {
	auto myfoo = Factory::create("Foo");
	myfoo->greeting();
	auto mybar = Factory::create("Bar");
	mybar->greeting();
	cout << "Foo existe ? " << (Factory::existe("Foo")?"oui":"non") << endl;
	cout << "koko existe ? " << (Factory::existe("koko")?"oui":"non") << endl;
	return 0;
}
*/







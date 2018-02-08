#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Tags : public vector<string>{
public:
	bool contient(string tag) { return ( std::find( begin(), end(), tag ) != end() ); }
};

class Carte;

class Effet {
	Effet( Carte* target ){}
	virtual void annuler() =0;
};


class Carte {
public:
	const string nom;
	Tags tags;
	vector<Effet> effets;
	int offense, defense, sacrifice, destruction;
	
};

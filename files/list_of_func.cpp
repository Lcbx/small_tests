#include <iostream>
#include<list>


using namespace std;

class Ara
{
public:
    Ara(int att = 0) : att_(att) {}
    bool afficher(int foo = 0)  { cout << att_;  return false; }
    bool setAtt(int att = 0)    { att_ = att;    return true; }
    bool multAtt(int mult = 1)  { att_ *= mult;  return true; }
    bool addAtt(int add = 0)    { att_ += add;   return true; }
private:
    int att_;
};


typedef bool (Ara::*DelayedFct) (int);
class Bebe {
public:
    Bebe(Ara* a, DelayedFct fct, int i) : origin(a), funct(fct), target(i){}
    bool act() { return (origin->*funct) (target); }
    Ara* origin;
    DelayedFct funct;
    int target;
};


class Coco : public list<Bebe> {
public:
    Coco() {}
    void cycle() {  for( Coco::iterator it = begin(); it != end(); it++){ bool getRid = it->act(); if (getRid){ erase(it--);} }  }
};

/*
int main() {
    Ara a(4);
    Bebe b(&a, &Ara::afficher, 0);
    b.act();
    Coco c;
    c.emplace_front(&a, &Ara::multAtt, 2);
    c.push_back(b);
    c.cycle();
    a.setAtt(0);
    c.emplace_front(&a, &Ara::addAtt, 1);
    c.push_front(*c.begin());
    c.cycle();
    cout << endl;
    return 0;
}
*/
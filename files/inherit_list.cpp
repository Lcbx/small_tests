#include<iostream>
#include<list>

using namespace std;

class bibli : public list<int>
{
public:
    bibli();
    ~bibli();
    void operator+=(int new_int);
    void afficher() const;
};

bibli::bibli(){}
bibli::~bibli(){}
void bibli::operator+=(int new_int) { push_back(new_int); };
void bibli::afficher() const {
    for( list<int>::const_iterator i = begin(); i != end(); i++) cout << *i << endl;
    }



/*
int main() {
    bibli test;
    for(int i = 0; i < 10; i++) test += i;
    test.afficher();
    return 0;
}
*/
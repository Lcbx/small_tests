#include <iostream>
#include <tuple>

using namespace std;

class A;

typedef void (A::*DelayedFct) (int);
typedef tuple<A*, DelayedFct, int> CompleteFct;

class A
{
public:
    A(int att) : att_(att) {}
    void setAtt(int att) { att_ = att; }
    int getAtt() { return att_; }
	
    static void act(A* a, DelayedFct d, int i){ (*(a).*d) (i); }
    static void act(CompleteFct that) { (*get<0>(that).*get<1>(that)) (get<2>(that)); }
	
private:
    int att_;
};

/*
int main(){
    A a(0);
    DelayedFct d = &A::setAtt;
    CompleteFct  c = make_tuple (&a, d, 7);
    A::act(c);
    cout << a.getAtt() << endl;
    A::act(&a, d, 3);
    cout << a.getAtt() << endl;
    return 0;
}
*/


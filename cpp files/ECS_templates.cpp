#include <iostream>

struct Vector {
	Vector(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
	double x, y, z;
	void print() {
		std::cout << "x " << x << ", y " << y << ", z " << z << "\n";
	}
};


// Components are sruct with mostly data
struct Position : public Vector {
	using Vector::Vector;
	double distance_from(const Position& pos) const {
		return x * pos.x + y * pos.y + z * pos.z;
	}
};
struct Vitesse : public Vector {
	using Vector::Vector;
	double norme() const {
		return x * x + y * y + z * z;
	}
};


//an interface so that all systems are accesible
struct Isystem {
	virtual void update(double dt) = 0;
};

// System are classes with mostly methods (make them static?) and pointers to the required Components
template<typename Object>
class Physics_module : public Isystem {

	Object& o;

public:

	//Physics_module() {}
	Physics_module(Object& obj) : o(obj) {}

	void update(double dt) {
		o.position.x += o.vitesse.x * dt;
		o.position.y += o.vitesse.y * dt;
		o.position.z += o.vitesse.z * dt;
	}

	void apply_force(double X, double Y, double Z) {
		o.vitesse.x += X;
		o.vitesse.y += Y;
		o.vitesse.z += Z;
	}
};


// an Entity is a patchwork of Components and Systems
struct Object {

	Position position = Position(0., 0., 0.);
	Vitesse vitesse = Vitesse(0., 1., 0.5);

	//templates
	// pros : less interfacing + check for component at compilation
	// cons : obtuse syntax like below
	Physics_module<Object> phys = Physics_module<Object>(*this);

	Object() {}
};


/*
int main() {

Object o1;
Object o2;

o2.phys.apply_force(0.2, -0.3, 0.1);

std::cout << "starting positions :\n";
o1.position.print();
o2.position.print();

std::cout << "starting speed :\n";
o1.vitesse.print();
o2.vitesse.print();

o1.phys.update(0.5);
o2.phys.update(0.5);

std::cout << "positions after 0.5 sec :\n";
o1.position.print();
o2.position.print();


int i;
std::cin >> i;
}
*/
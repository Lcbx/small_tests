#include <iostream>


struct Vec {
	int x, y, z;
	Vec(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
};


struct Vec3 {
	int x, y, z;
	Vec3(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
};

template<typename from, typename to>
to conversion(from f) { return to(f.x,f.y,f.z); }

template<typename T>
void print(T f) { std::cout << f.x << " " << f.y << " " << f.z << "\n"; }

Vec conversion(Vec3 f) { return Vec(f.x, f.y, f.z); }
Vec3 conversion(Vec f) { return Vec3(f.x, f.y, f.z); }

/*
int main() {

	Vec3 a(0, 2, 3);
	print(a);

	Vec v = conversion<Vec3, Vec>(a);
	print(v);

	v = conversion(a);
	print(v);

	int i; std::cin >> i;

	return 0;
}
*/
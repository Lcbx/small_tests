#pragma once
#include <cstdint>
#include <vector>
#include <array>


const int INTERNAL_ARRAYS_SIZE = 32;


template<typename T>
class VirtualArray {
	

	typedef std::array<T, INTERNAL_ARRAYS_SIZE> Slab;
	std::vector<Slab*> _data;

	unsigned int _size = 0;

	inline T& get(std::uint32_t index) { return (*(_data[index / INTERNAL_ARRAYS_SIZE]))[index % INTERNAL_ARRAYS_SIZE]; }

public:

	unsigned int size() { return _size; }

	std::vector<Slab*>& data() { return _data; }
	
	T& operator[](unsigned int index) {	return get(index); }


	void push(T item) {
		if (_size + 1 > INTERNAL_ARRAYS_SIZE * _data.size()) {
			_data.push_back(new Slab());
		}
		get(_size) = item;
		_size++;
	}

	T& pop() { _size--;  return get(_size); }

	T& peek() { return get(_size -1); }


	~VirtualArray() {
		for (auto slab : _data)
			if( slab != nullptr )
				delete slab;
	}
};



/*
#include<iostream>
int main() {


	VirtualArray<int> p;


	for (int i = 0; i < 17; i++) p.push(i);

	p.push(0);

	//p[4] = 500;

	//for (int i = 0; i < 10; i++) p.pop();

	for (int i = 0; i < 64; i += 2) p.push(i);

	for (int i = 0; i < 256; i++) p.push(i);

	
	//int count = 0; while (p.size() > 0) p.pop(); std::cout << std::endl << "removed " << count << std::endl << std::endl;	
	
	//std::cout << p.peek() << std::endl;
	
	//for (int i = 0; i < p.size; i++) std::cout << p[i] << std::endl;

	std::cout << std::endl;
	std::cout << "total stored " << p.size() << std::endl << std::endl;
	std::cout << "number of slabs " << p.data().size() << std::endl << std::endl;
	std::cout << "vector capacity " << p.data().capacity() << std::endl << std::endl;
	std::cout << "available slots " << p.data().size() * INTERNAL_ARRAYS_SIZE - p.size() << std::endl << std::endl;
	std::cout << "total slots " << p.data().size() * INTERNAL_ARRAYS_SIZE << std::endl << std::endl;
	std::cout << "percent used " << (float(p.size()))/ (p.data().size() * INTERNAL_ARRAYS_SIZE)*100 << std::endl << std::endl;


	int g = 0;
	std::cin >> g;

	return 0;
}
*/
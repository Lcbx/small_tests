#include <map>
#include <unordered_map>

// O(1) direct lookup
// O(1) average direct insertion/deletion
// naturally sorted iteration
// can access a key, then iterate to closest keys
// O(log n) comparative search (lower_bound, etc)
template<typename T, typename U> struct HybridMap {

	// keeps an ordered map for ordered iteration
	std::map<T, U> oMap;
	// uses a hashmap for direct access, that stores iterator to the ordered map
	std::unordered_map<T, typename std::map<T, U>::iterator> uMap;

	HybridMap() {}

	void set(T key, U item) {
		// should work, but doesnt
		//	auto ret = oMap.insert(std::pair<T, U>(key, item)).first;
		// *ret = item
		oMap[key] = item;
		uMap[key] = oMap.find(key); // = ret
	}

	void erase(U key) {
		auto it = uMap.erase(key);
		oMap.erase(it);
	}

	bool has(T key) {
		return uMap.find(key) != uMap.end();
	}

	auto at(T key) {
		return uMap[key];
	}
};

/*
#include <string>
#include <iostream>
int main() {
	HybridMap<int, float> m;
	
	for (int i = 0; i<100; i++)
		m.set(i, i);

	for (auto it = m.at(50); it != m.oMap.end(); it++)
		std::cout << (*it).second << std::endl;
	std::cout << m.has(49) << std::endl;
	m.erase(49);
	std::cout << m.has(49) << std::endl;
	std::cout << m.oMap.size() << std::endl;
	std::cout << m.uMap.size() << std::endl;

	return 0;
}*/



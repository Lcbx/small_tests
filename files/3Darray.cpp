#pragma once

#include <./glm/common.hpp>

#include <cstdint>

const int SIZE = 3;
const int SIZEx3 = SIZE * SIZE * SIZE;

template<typename T>
struct SpatialArray {

	union {
		// dispatched this way : (x, y, z)
		// so to get x you have to divide by SIZE^2
		// to get y you have to divide by SIZE then modulo SIZE
		// to get z you have to modulo SIZE
		T simple[SIZEx3];
		//simpler 3D access this way though :)
		T spatial[SIZE][SIZE][SIZE];
	};

	SpatialArray() {}
};

struct Block {

	std::uint16_t id = Block::air;
	enum types {air, other};

	int getType() { return id >> 4; }

	int getHealth() { return id & 0xf; }
	void setHealth(int health) { id = id & 0xfff0 + health; }

	Block() {}
};

struct Chunk {

	SpatialArray<Block> data;

	void makeEmpty() {
		for (int i = 0; i < SIZEx3; i++) {
			data.simple[i].id = Block::air;
		}
	}
	bool empty() {
		for (int i = 0; i < SIZEx3; i++) {
			if (data.simple[i].id != Block::air) return false;
		}
		return true;
	}
	
	Chunk() {}
};


struct ChunkVisitor {
	virtual void visitChunk(Chunk& chunk) = 0;
};

struct BlockVisitor : public ChunkVisitor {
	void visitChunk(Chunk& chunk) {
		for (int i = 0; i < SIZEx3; i++) {
			visitBlock(chunk.data.simple[i]);
		}
	}
	virtual void visitBlock(Block& chunk) = 0;
};


struct World {

	SpatialArray<Chunk*> data;

	Block zero;

	void makeEmpty() {
		for (int i = 0; i < SIZEx3; i++) {
			data.simple[i] = nullptr;
		}
	}

	bool empty() {
		for (int i = 0; i < SIZEx3; i++) {
			if (data.simple[i] != nullptr && !data.simple[i]->empty()) {
				return false;
			}
		}
		return true;
	}

	Block get(glm::vec3 pos) {
		glm::ivec3 iCoord = glm::ivec3(pos);
		glm::ivec3 iChunkCoord = iCoord / SIZE;
		Chunk* chunk = data.spatial[iChunkCoord.x][iChunkCoord.y][iChunkCoord.z];
		if (chunk == nullptr)
			return zero;
		glm::ivec3 iblockCoord = iCoord % SIZE;
		return chunk->data.spatial[iblockCoord.x][iblockCoord.y][iblockCoord.z];
	}
	void set(glm::vec3 pos, Block::types type) {
		glm::ivec3 iCoord = glm::ivec3(pos);
		glm::ivec3 iChunkCoord = iCoord / SIZE;
		glm::ivec3 iblockCoord = iCoord % SIZE;
		Chunk* chunk = data.spatial[iChunkCoord.x][iChunkCoord.y][iChunkCoord.z];
		if (chunk == nullptr) {
			chunk = new Chunk();
			chunk->makeEmpty();
		}
		chunk->data.spatial[iblockCoord.x][iblockCoord.y][iblockCoord.z].id = type;
	}

	void receive(ChunkVisitor* visitor) {
		for (int i = 0; i < SIZEx3; i++) {
			if (data.simple[i] != nullptr) visitor->visitChunk(*data.simple[i]);
		}
	}

	World() {}
};





/*

#include<iostream>
int main() {


	std::cout << "\n\nSpatialArray \n\n";
	SpatialArray<int> p;

	int n = 2;
	p.simple[n] = 1;
	std::cout << "z test " << p.spatial[0][0][n] << "\n";

	p.simple[n * SIZE] = 2;
	std::cout << "y test " << p.spatial[0][n][0] << "\n";

	p.simple[n * SIZE * SIZE] = 3;
	std::cout << "x test " << p.spatial[n][0][0] << "\n";


	std::cout << "\n\nBlock \n\n";
	Block b;
	b.id = 0x0012;
	std::cout << "type " << b.getType() << "\n";
	std::cout << "health " << b.getHealth() << "\n";

	std::cout << "air code " << Block::air << "\n";

	std::cout << "size " << sizeof(Block) << "\n";
	std::cout << "size of 16 bit " << sizeof(std::uint16_t) << "\n";


	std::cout << "\n\nChunk \n\n";
	Chunk c;
	c.makeEmpty();

	//for (int i = 0; i < SIZEx3; i++) {
	//	std::cout << c.data.simple[i].id << " ";
	//}

	std::cout << "first empty() : " << c.empty() << "\n";

	c.data.spatial[0][0][1].id = b.id;
	std::cout << "second empty() : " << c.empty() << "\n";


	std::cout << "\n\nWorld \n\n";
	World w;
	w.makeEmpty();
	std::cout << "first empty() : " << w.empty() << "\n";

	glm::ivec3 chunkPos(n, 0, 1);
	w.data.spatial[chunkPos.x][chunkPos.y][chunkPos.z] = &c;
	std::cout << "second empty() : " << w.empty() << "\n";

	std::cout << "SpatialArray style test " << w.data.spatial[chunkPos.x][chunkPos.y][chunkPos.z]->data.spatial[0][0][1].id << "\n";

	glm::vec3 pos = (chunkPos * SIZE) + glm::ivec3(0, 0, 1);
	std::cout << "access to block : " << w.get(pos).id << "\n";
	
	glm::vec3 pos2 = pos + glm::vec3(1, 0, 0);
	std::cout << "access to air block : " << w.get(pos2).id << "\n";


	w.set(pos2, Block::other);
	std::cout << "write to air block : " << w.get(pos2).id << "\n";

	int g = 0;
	std::cin >> g;

	return 0;
}

*/
#include "Chunk.h"

void Chunk::Init(std::size_t blockSize, unsigned char blocks) {
	pData = new unsigned char[blockSize * blocks];
	firstAvailableBlock = 0;
	blocksAvailable = blocks;
	unsigned char i = 0;
	unsigned char *ptr = pData;
	for (; i < blocks; ptr += blockSize) {
		*(ptr) = ++i;
	}
}

void* Chunk::Allocate(std::size_t blockSize) {
	if (blocksAvailable == 0)
		return nullptr;
	auto ptr = (pData + (blockSize * firstAvailableBlock));
	firstAvailableBlock = *ptr;
	blocksAvailable--;
	return ptr;
}

void Chunk::Deallocate(void *p, std::size_t blockSize) {
	unsigned char* toRelease = static_cast<unsigned char*>(p);
	//// alignment check
	assert((toRelease - (pData+firstAvailableBlock*blockSize )) % blockSize == 0);
	*toRelease = firstAvailableBlock;
	firstAvailableBlock = static_cast<unsigned char>((p - pData) / blockSize);
	/// truncation check
	assert(firstAvailableBlock == (p - pData) / blockSize);
	blocksAvailable++;
}

void Chunk::Release() { delete[] pData; }

FixedSizeAllocator::FixedSizeAllocator(std::size_t blockSize, unsigned char blocks): blockSize_(blockSize) , blocks_(blocks) { allocChunk_ = nullptr; deallocChunk_ = nullptr;}

void* FixedSizeAllocator::Allocate() {
	if(!allocChunk_ || allocChunk_->blocksAvailable == 0){
		allocChunk_ = new Chunk();
		allocChunk_.Init(blockSize_,blocks_);
		chunks.push_back(allocChunk_);
	}
	return allocChunk_->Allocate(blockSize_);
}




#ifndef CHUNK_HFILE
#define CHUNK_HFILE
class Chunk {
public:
  void Init(std::size_t blockSize, unsigned char blocks);
  void *Allocate(std::size_t blockSize);
  void Deallocate(void *p, std::size_t blockSize);
  void Release();
private:
  unsigned char *pData;
  unsigned char firstAvailableBlock;
  unsigned char blocksAvailable;
};

class FixedSizeAllocator {
	public:
		FixedSizeAllocator(std::size_t blockSize, unsigned char blocks);
		FixedSizeAllocator() = delete;
		void* Allocate();
		void Deallocate(void* p);

	private:
		size_t blockSize_;
		unsigned char blocks_;
		typedef std::vector<Chunk*> Chunks;
		Chunks chunks_;
		Chunk* allocChunk_;
		Chunk* deallocChunk_;
};

#endif

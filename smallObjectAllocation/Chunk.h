#ifndef CHUNK_HFILE
#define CHUNK_HFILE
class Chunk {
  void Init(std::size_t blockSize, unsigned char blocks);
  void *Allocate(std::size_t blockSize);
  void Deallocate(void *p, std::size_t blockSize);
  void Release();

public:
  unsigned char *pData;
  unsigned char firstAvailableBlock;
  unsigned char blocksAvailable;
};

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

void *Chunk::Allocate(std::size_t blockSize) {
  if (blocksAvailable == 0)
    return nullptr;
  auto ptr = (pData + (blockSize * firstAvailableBlock));
  firstAvailableBlock = *ptr;
  blocksAvailable--;
  return ptr;
}

void Chunk::Deallocate(void *p, std::size_t blockSize) {
  //// alignment check
  assert((p - (pData + firstAvailableBlock * blockSize)) % blockSize == 0);
  *p = firstAvailableBlock;
  firstAvailableBlock = static_cast<unsigned char>((p - pData) / blockSize);
  /// truncation check
  assert(firstAvailableBlock == (p - pData) / blockSize);
  blocksAvailable++;
}

void Release() { delete[] pData; }
#endif

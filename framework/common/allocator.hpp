//
// Created by Chen.Zr on 2020/3/21.
//

#ifndef GAME_ENGINE_ALLOCATOR_HPP
#define GAME_ENGINE_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>

namespace engine{
    struct BlockHeader{
        BlockHeader* pNext_ = nullptr;
    };
    struct PageHeader{
        PageHeader* pNext_ = nullptr;
        BlockHeader* Blocks(){
            return reinterpret_cast<BlockHeader*>(this + 1);
        }
    };

    class Allocator {
    public:
        static const uint8_t kPatternAlign = 0xFC;
        static const uint8_t kPatternAlloc = 0xFD;
        static const uint8_t kPatternFree  = 0xFE;

        Allocator(size_t data_size, size_t page_size, size_t alignment);
        ~Allocator();

        void Reset(size_t data_size, size_t page_size, size_t alignment);

        void* Allocate();
        void Free(void* p);
        void FreeAll();

        BlockHeader* NextBlock(BlockHeader* pBlock);

#if defined (MY_DEBUG)
        void FillFreePage(PageHeader* page);
        void FillFreeBlock(BlockHeader* block);
        void FillAllocatedBlock(BlockHeader* block);
#endif

        Allocator(const Allocator& clone) = delete;
        Allocator &operator=(const Allocator &rhs) = delete;

    private:
        size_t m_szDataSize;
        size_t m_szPageSize;
        size_t m_szAlignmentSize;
        size_t m_szBlockSize;
        uint32_t m_nBlocksPerPage;

        PageHeader* m_pPageList;

        BlockHeader* m_pFreeList;

        uint32_t m_nPages;
        uint32_t m_nBlocks;
        uint32_t m_nFreeBlocks;
    };
}

#endif //GAME_ENGINE_ALLOCATOR_HPP

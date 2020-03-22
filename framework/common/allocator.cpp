//
// Created by Chen.Zr on 2020/3/21.
//

#include "allocator.hpp"
#include <cassert>
#include <cstring>

#ifndef ALIGN
#define ALIGN(x, a)         (((x) + ((a) - 1)) & ~((a) - 1))
#endif

engine::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
        : m_pPageList(nullptr), m_pFreeList(nullptr){
    Reset(data_size, page_size, alignment);
}

engine::Allocator::~Allocator() {
    FreeAll();
}

void engine::Allocator::Reset(size_t data_size, size_t page_size, size_t alignment) {
    FreeAll();

    m_szDataSize = data_size;
    m_szPageSize = page_size;

    size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;

#if defined (MY_DEBUG)
    assert((alignment > 0 && (alignment & (alignment - 1))) == 0);
#endif
    m_szBlockSize = ALIGN(minimal_size, alignment);

    m_szAlignmentSize = m_szBlockSize - minimal_size;

    m_nBlocksPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

void *engine::Allocator::Allocate() {
    if (!m_pFreeList){
        auto pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
        pNewPage -> pNext_ = nullptr;
        ++m_nPages;
        m_nBlocks += m_nBlocksPerPage;
        m_nFreeBlocks += m_nBlocksPerPage;
#if defined(MY_DEBUG)
        FillFreePage(pNewPage);
#endif
        if (m_pPageList){
            pNewPage -> pNext_ = m_pPageList;
        }
        m_pPageList = pNewPage;
        BlockHeader* pNewBlock = pNewPage -> Blocks();
        for (int i = 0; i < m_nBlocksPerPage; ++i) {
            pNewBlock -> pNext_ = NextBlock(pNewBlock);
            pNewBlock = NextBlock(pNewBlock);
        }
        pNewBlock -> pNext_ = nullptr;

        m_pFreeList = pNewPage -> Blocks();
    }
    BlockHeader* freeBlock = m_pFreeList;
    m_pFreeList = m_pFreeList -> pNext_;
    --m_nFreeBlocks;
#if defined(MY_DEBUG)
    FillAllocatedBlock(freeBlock);
#endif
    return reinterpret_cast<void*>(freeBlock);
}

void engine::Allocator::Free(void *p) {
    auto block = reinterpret_cast<BlockHeader*>(p);
#if defined(MY_DEBUG)
    FillFreeBlock(block);
#endif
    block -> pNext_ = m_pFreeList;
    m_pFreeList = block;
    ++m_nFreeBlocks;
}

void engine::Allocator::FreeAll() {
    PageHeader* pPage = m_pPageList;
    while (pPage){
        PageHeader *p = pPage;
        pPage = pPage -> pNext_;
        delete [] reinterpret_cast<uint8_t*>(p);
    }
    m_pPageList = nullptr;
    m_pFreeList = nullptr;

    m_nPages = 0;
    m_nBlocks = 0;
    m_nFreeBlocks = 0;
}

engine::BlockHeader *engine::Allocator::NextBlock(engine::BlockHeader *pBlock) {
    return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize);
}

#if defined(MY_DEBUG)
void engine::Allocator::FillFreePage(engine::PageHeader *page) {
    page -> pNext_ = nullptr;

    BlockHeader* block = page -> Blocks();
    for (int i = 0; i < m_nBlocksPerPage; ++i) {
        FillFreeBlock(block);
        block = NextBlock(block);
    }
}

void engine::Allocator::FillFreeBlock(engine::BlockHeader *block) {
    std::memset(block, kPatternFree, m_szBlockSize - m_szAlignmentSize);
    std::memset(reinterpret_cast<uint8_t*>(block) + m_szBlockSize - m_szAlignmentSize, kPatternAlign, m_szAlignmentSize);
}

void engine::Allocator::FillAllocatedBlock(engine::BlockHeader *block) {
    std::memset(block, kPatternFree, m_szBlockSize - m_szAlignmentSize);
    std::memset(reinterpret_cast<uint8_t*>(block) + m_szBlockSize - m_szAlignmentSize, kPatternAlign, m_szAlignmentSize);
}
#endif

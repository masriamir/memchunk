#ifndef __MEMCHUNK_H__
#define __MEMCHUNK_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct MemChunk {
    uint32_t ptr;
    uint32_t size;
    uint8_t *data;
} MemChunk;

MemChunk *new_memchunk(const uint32_t);
bool free_data(MemChunk *const);
bool free_memchunk(MemChunk *);

bool resize(MemChunk *const, const uint32_t);
bool clear(MemChunk *const);
bool is_empty(const MemChunk *);

void seek_memchunk(MemChunk *const, const uint32_t, const uint32_t);

bool read(void *const, MemChunk *const, const uint32_t);
bool read_ofs(void *const, MemChunk *const, const uint32_t, const uint32_t);
bool write(MemChunk *, const void *, const uint32_t);
bool write_ofs(MemChunk *, const void *, const uint32_t, const uint32_t);

#endif

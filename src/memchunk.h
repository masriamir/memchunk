#ifndef __MEMCHUNK_H__
#define __MEMCHUNK_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct MemChunk {
    uint32_t ptr;
    uint32_t size;
    uint8_t *data;
} MemChunk;

MemChunk *new_chunk( const uint32_t );
bool free_chunk_data( MemChunk *const );
bool free_chunk( MemChunk * );

bool resize_chunk( MemChunk *const, const uint32_t );
bool clear_chunk( MemChunk *const );
bool is_chunk_empty( const MemChunk * );

void seek_chunk( MemChunk *const, const uint32_t, const uint32_t );

bool read_chunk( void *const, MemChunk *const, const uint32_t );
bool read_chunk_ofs( void *const, MemChunk *const, const uint32_t,
                     const uint32_t );

bool write_chunk( MemChunk *, const void *, const uint32_t );
bool write_chunk_ofs( MemChunk *, const void *, const uint32_t,
                      const uint32_t );

#endif

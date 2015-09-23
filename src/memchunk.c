#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "memchunk.h"

MemChunk *new_memchunk(const uint32_t size) {
    MemChunk *mc;

    /* allocation memory for memchunk */
    if (!(mc = malloc(sizeof(*mc)))) {
        fprintf(stderr, "memchunk:new_memchunk - memchunk allocation failed\n");
        return NULL;
    }

    /* set size and position */
    mc->ptr = 0;
    mc->size = size;

    /* make sure size is valid */
    if (size > 0) {
        /* if we cannot allocate the data set it to NULL */
        if(!(mc->data = malloc(size))) {
            fprintf(stderr, "memchunk:new_memchunk - data allocation failed\n");
            mc->data = NULL;
        }
    } else {
        mc->data = NULL;
    }

    return mc;
}

bool free_data(MemChunk *const mc) {
    /* check for valid data */
    if (mc->data) {
        free(mc->data);
        mc->data = NULL;
        return true;
    }

    return false;
}

bool free_memchunk(MemChunk *mc) {
    /* check for valid memchunk */
    if (mc) {
        free_data(mc);

        free(mc);
        mc = NULL;

        return true;
    }

    return false;
}

bool resize(MemChunk *mc, const uint32_t new_size) {
    if (new_size < 1) {
        return false;
    }

    mc->data = realloc(mc->data, new_size);
    if (!mc->data) {
        fprintf(stderr, "memchunk:resize - allocation of %u bytes failed\n", new_size);
        return false;
    }

    mc->size = new_size;

    /* if we decreased the size set the postion to the end of the chunk */
    if (mc->ptr > mc->size) {
        mc->ptr = mc->size;
    }

    return true;
}

bool clear(MemChunk *const mc) {
    if (!is_empty(mc)) {
        mc->ptr = 0;
        mc->size = 0;
        free_data(mc);
        return true;
    }

    return false;
}

bool is_empty(const MemChunk *mc) {
    return mc->size == 0 && !mc->data;
}

void seek_memchunk(MemChunk *const mc, const uint32_t offset, const uint32_t start) {
    if (start == SEEK_CUR) {
        /* offset based on current position */
        mc->ptr += offset;
        if (mc->ptr > mc->size) {
            mc->ptr = mc->size;
        }
    } else if (start == SEEK_SET) {
        /* offset based on beginning of file */
        mc->ptr = offset;
        if (mc->ptr > mc->size) {
            mc->ptr = mc->size;
        }
    } else if (start == SEEK_END) {
        /* offset based on end of file */
        if (offset > mc->size) {
            mc->ptr = 0;
        } else {
            mc->ptr = mc->size - offset;
        }
    }
}

bool read(void *const buf, MemChunk *const mc, const uint32_t size) {
    /* valid destination and source data */
    if (!mc->data || !buf) {
        return false;
    }

    /* make sure we are not reading past the end of the chunk */
    if (mc->ptr + size > mc->size) {
        return false;
    }

    /* copy the mem chunk to the given buffer and advance the position */
    memcpy(buf, mc->data + mc->ptr, size);
    mc->ptr += size;

    return true;
}

bool write(MemChunk *mc, const void *data, const uint32_t size) {
    /* valid data to write */
    if (!data) {
        return false;
    }

    /* resize the memchunk if we are trying to write past the end of the chunk */
    if (mc->ptr + size > mc->size) {
        resize(mc, mc->size + size);
    }

    /* copy the data and set the new position */
    memcpy(mc->data + mc->ptr, data, size);
    mc->ptr += size;

    return true;
}

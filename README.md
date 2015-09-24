# MemChunk

## Overview

C library to handle memory allocation and related i/o.

## Build

* Run `make` to produce static and dynamic libraries.

## Notes

* New chunks can be created with `new_memchunk`. They must be freed using `free_memchunk`.
* Supports seeking similar to `fseek`.
* Can read from or write to chunk.

## TODO

* Arbitrary access to memory.
* Read and write directly from/to files.
* Create chunk from existing data.
* Additional seek options when using the offset versions of read/write.
* Memset-like functionality.

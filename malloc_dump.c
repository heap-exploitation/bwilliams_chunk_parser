// Ben Williams
// January 2025

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void dump(void* ptr);

int main(int argc, char** argv) {
	char* dummymalloc = malloc(1024);

	for (int i = 0; i < 1024; i++) {
		dummymalloc[i] = 'a';
	}

	dump(dummymalloc);

	return 0;
}



void determine_low_bits_info(void* ptr) {
	size_t* info_ptr = ptr;
	info_ptr--;

	size_t metadata = *(size_t*) info_ptr;
	
	// First bit -- P
	if (metadata & 1 == 1) {
		printf("The previous chunk is in use\n");
	} else {
		printf("The previous chunk is not in use\n");
	}
	

	// Second bit -- M
	
	if (metadata & 2 == 2) {
		printf("The chunk was allocated with an mmap call\n");
	} else {
		printf("The chunk was allocated with a malloc call\n");
	}

	

	// Third bit -- A
	if (metadata & 4 == 4) {
		printf("The chunk comes from mmap'd memory, and is not in the main arena\n");
	} else {
		printf("The chunk comes from the main arena\n");
	}


}



void determine_chunk_size(void* ptr) {
	size_t* info_ptr = ptr;
	info_ptr--;

	size_t metadata = *(size_t*) info_ptr;

	size_t size_mask = ~7;

	size_t chunk_size = metadata & size_mask; // clears the low 3 bits

	printf("Chunk size is 0x%zx\n", chunk_size);
}


void dump(void* ptr) {
	printf("Pointer address: %p\n", ptr);

	determine_low_bits_info(ptr);
	
	determine_chunk_size(ptr);
}

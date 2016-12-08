#include "varint.h"

int test_varint() {

	uint64_t u64 = 300;
	size_t buffer_size = 256;
	char buffer[buffer_size];

	memset(buffer, 0, 256);

	unsigned char results;
	varint_encode(u64, buffer, buffer_size, &results);

	unsigned int pos0 = buffer[0];
	if ( pos0 != 172) {
		printf("Expected %d but got %d at position 0\n", 172, pos0);
		return 0;
	}
	if (buffer[0] == 0) {
		printf("should not be zero");
		return 0;
	}

	return 1;
}

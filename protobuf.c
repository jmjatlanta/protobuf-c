#include <stdint.h>

#include "varint.h"
#include "protobuf.h"

// size_t uvarint_encode64(uint64_t val, uint8_t buf[], size_t bufsize)

/***
 * Encode the incoming_struct into a protobuf
 * @param incoming_struct the struct to get data from
 * @param types the field types in the struct
 * @param types_array_size the array size of the types
 * @param buffer where to put the results
 * @param max_buffer_length prevents buffer overflows
 * @returns number of bytes written
 */
int protobuf_encode(void* incoming_struct, enum WireType* types, size_t types_array_size, char* buffer, size_t max_buffer_length) {
	int counter = 0;
	for(int i = 0; i < types_array_size; i++) {
		// push the field number and wire type together
		unsigned int types_val = types[i];
		unsigned int field_no = (i + 1) << 3;
		unsigned long long field = field_no | types_val;
		unsigned char bytes_processed;
		varint_encode(field, buffer, max_buffer_length, &bytes_processed);
		counter += (unsigned int)bytes_processed;
		//counter += uvarint_encode64(150, &buffer[counter], max_buffer_length - counter);
	}
	return counter;
}

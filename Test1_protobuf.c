#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protobuf.h"
#include "varint.h"
#include "Test1_protobuf.h"

enum WireType Test1_message_fields[] = { WIRETYPE_VARINT };

int Test1_protobuf_encode(struct Test1* incoming, unsigned char* buffer, size_t max_buffer_length, size_t* bytes_written) {
	int counter = 0;
	for(int i = 0; i < 1; i++) {
		// push the field number and wire type together
		unsigned int types_val = Test1_message_fields[i];
		unsigned int field_no = (i + 1) << 3;
		unsigned long long field = field_no | types_val;
		unsigned char bytes_processed;
		char* b = (char*)buffer;
		varint_encode(field, b, max_buffer_length, &bytes_processed);
		counter += (unsigned int)bytes_processed;
		varint_encode(incoming->a, &b[counter], max_buffer_length - counter, &bytes_processed);
		counter += (unsigned int)bytes_processed;
	}
	*bytes_written = counter;
	return 1;
}

int Test1_protobuf_decode(unsigned char* buffer, size_t buffer_length, struct Test1** output) {
	int pos = 0;
	*output = (struct Test1*)malloc(sizeof(struct Test1));
	if (*output == NULL)
		return 0;

	while (pos < buffer_length) { // loop through buffer
		unsigned char bytes_read;
		char* b = (char*) buffer;
		unsigned long long result = varint_decode(&b[pos], buffer_length - pos, &bytes_read);
		pos += (unsigned int)bytes_read;
		int field_no = result >> 3;
		int field_type = field_no & result;
		switch (field_no) {
			case (1):
				(*output)->a = varint_decode(&b[pos], buffer_length - pos, &bytes_read);
				pos += (unsigned int)bytes_read;
				break;
		}
	}
	return 1;
}

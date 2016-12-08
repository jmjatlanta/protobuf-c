
/***
 * This...
 *
 * message Test1 {
 *  required int32 a = 1;
 * }
 *
 * should generate Test1_protobuf.h and c that contains this...
 *
 * enum WireType Test1_message_fields[] = { WIRETYPE_VARINT }
 *
 * struct Test1 {
 * 	int a;
 * }
 *
 * int Test1_protobuf_encode(struct Test1* incoming, unsigned char* buffer, size_t max_buffer_length, size_t* bytes_written);
 * int Test1_protobuf_decode(unsigned char* buffer, size_t buffer_length, struct Test1** output);
 */

#include "Test1_protobuf.h"

int test_rightshift() {
	struct Test1 test1;
	test1.a = 0;

	size_t buffer_size = 256;
	unsigned char buffer[buffer_size];
	memset(buffer, 0, 256);

	int retVal = 0;
	size_t bytes_written = 0;
	retVal = Test1_protobuf_encode(&test1, buffer, buffer_size, &bytes_written);

	if (retVal == 0) {
		printf("Error encoding\n");
		return 0;
	}

	if (bytes_written != 2) {
		printf("Incorrect number of bytes written. Expected 2, but got %d\n", retVal);
		return 0;
	}

	unsigned int pos0 = buffer[0];
	unsigned int pos1 = buffer[1];

	if (pos0 != 8) {
		printf("Results at pos 0 not as expected\n");
		return 0;
	}

	if (pos1 != 0) {
		printf("Results at pos 1 not as expected\n");
		return 0;
	}

	return 1;
}

int test_write_simple() {
	struct Test1 test1;
	test1.a = 150;

	size_t buffer_size = 256;
	unsigned char buffer[buffer_size];
	memset(buffer, 0, 256);

	int retVal = 0;
	size_t bytes_written = 0;
	retVal = Test1_protobuf_encode(&test1, buffer, buffer_size, &bytes_written);

	if (retVal == 0) {
		printf("Error encoding\n");
		return 0;
	}

	if (bytes_written != 3) {
		printf("Incorrect number of bytes written. Expected 3, but got %d\n", retVal);
		return 0;
	}

	unsigned int pos0 = buffer[0];
	unsigned int pos1 = buffer[1];
	unsigned int pos2 = buffer[2];

	if (pos0 != 8 || pos1 != 96 || pos2 != 1) {
		printf("Results not as expected\n");
		return 0;
	}

	return 1;
}

/***
 * Helper to derived protobuf objects
 */
#include <stdint.h>
#include <string.h>

#include "varint.h"
#include "protobuf.h"

/***
 * encode a string into the buffer
 * @param field_number the field number
 * @param field_type the field type
 * @param incoming the string value
 * @param buffer the pointer to where to place the encoded value
 * @param max_buffer_length the buffer length remaining
 * @param bytes_written the number of bytes written
 * @returns true(1) on success
 */
int protobuf_encode_string(int field_number, enum WireType field_type, const char* incoming, unsigned char* buffer,
		size_t max_buffer_length, size_t* bytes_written) {
	// push the field number and wire type together
	unsigned int field_no = field_number << 3;
	unsigned long long field = field_no | field_type;
	size_t bytes_processed;
	// field type & number
	varint_encode(field, buffer, max_buffer_length, &bytes_processed);
	*bytes_written += bytes_processed;
	// field size
	varint_encode(strlen(incoming), &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_processed);
	*bytes_written += bytes_processed;
	// field value
	memcpy(&buffer[*bytes_written], incoming, strlen(incoming));
	*bytes_written += strlen(incoming);
	return 1;
}

/***
 * encode a varint into the buffer
 * @param field_number the field number
 * @param field_type the field type
 * @param incoming the value
 * @param buffer the pointer to where to place the encoded value
 * @param max_buffer_length the buffer length remaining
 * @param bytes_written the number of bytes written
 * @returns true(1) on success
 */
int protobuf_encode_varint(int field_number, enum WireType field_type, unsigned long long incoming, unsigned char* buffer,
		size_t max_buffer_length, size_t* bytes_written) {
	// push the field number and wire type together
	unsigned int field_no = field_number << 3;
	unsigned long long field = field_no | field_type;
	size_t bytes_processed;
	// field type & number
	varint_encode(field, buffer, max_buffer_length, &bytes_processed);
	*bytes_written += bytes_processed;
	// field value
	varint_encode(incoming, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_processed);
	*bytes_written += bytes_processed;
	return 1;

}

/**
 * Pull a string from the protobuf buffer
 * @param the buffer, positioned at the field size
 * @param buffer_length the buffer length
 * @param results the results (NOTE: will allocate memory)
 * @param bytes_read the number of bytes read
 * @returns true(1) on success
 */
int protobuf_decode_string(const unsigned char* buffer, size_t buffer_length, char** results, size_t* bytes_read) {
	size_t pos = 0;
	// grab the field size
	int length = varint_decode(&buffer[pos], buffer_length - pos, bytes_read);
	pos += *bytes_read;

	// allocate memory
	*results = malloc(sizeof(char) * length);
	if ((*results) == NULL)
		return 0;

	// copy the string
	memcpy((*results), &buffer[pos], length);
	pos += length;
	*bytes_read = pos;

	return 1;
}

/***
 * retrieve field number and field type from current buffer at position 0
 * @param buffer the incoming buffer
 * @param buffer_length the length of the buffer
 * @param field_no the resultant field number
 * @param field_type the field type
 * @param bytes_read the number of bytes read from the buffer
 */
int protobuf_decode_field_and_type(const unsigned char* buffer, int buffer_length, int *field_no, enum WireType *field_type, size_t* bytes_read) {
	unsigned long long field = varint_decode(buffer, buffer_length, bytes_read);
	*field_no = field >> 3;
	*field_type = field | *field_no;
	return 1;
}




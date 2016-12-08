#ifndef _VARINT_H_
#define _VARINT_H_

/**
 * Encode an unsigned long long into a varint
 * @param n the number to encode
 * @param buf where to put the results
 * @param len the length of buf
 * @param bytes the length written
 * @returns a pointer to the buf
 */
char* varint_encode(unsigned long long n, char* buf, int len, unsigned char* bytes);

/***
 * decode a varint
 * @param buf the buffer that contains the varint
 * @param len the length of the buffer
 * @param bytes number of bytes processed
 * @returns the value decoded
 */
unsigned long long varint_decode(char* buf, int buf_len, unsigned char* bytes);

/**
 *
 */
int varint_encoding_length(unsigned long long n);

#endif

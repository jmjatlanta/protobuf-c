/*
 * protobuf.h
 *
 *  Created on: Dec 7, 2016
 *      Author: JohnJones
 */

#ifndef __PROTOBUF_H__
#define __PROTOBUF_H__

#include <stdio.h>
#include <stdint.h>

enum WireType {
	WIRETYPE_VARINT,
	WIRETYPE_64BIT,
	WIRETYPE_LENGTH_DELIMITED,
	WIRETYPE_START_GROUP,
	WIRETYPE_END_GROUP,
	WIRETYPE_32BIT
};

#endif /* PROTOBUF_H_ */

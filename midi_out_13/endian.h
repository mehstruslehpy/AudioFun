#ifndef ENDIAN_
#define ENDIAN_
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//return whether current machine is little or big endian
bool littleEndian();
//return whether current machine is little or big endian
bool bigEndian();
//byte swap unsigned 16 bit integer
uint16_t swap_uint16(uint16_t val);
//byte swap signed 16 bit integer
int16_t swap_int16(int16_t val);
//byte swap unsigned 32 bit integer
uint32_t swap_uint32(uint32_t val);
//byte swap signed 32 bit integer
int32_t swap_int32(int32_t val);
//byte swap signed 64 bit integer
int64_t swap_int64( int64_t val );
//byte swap unsigned 64 bit integer
uint64_t swap_uint64(uint64_t val);

#endif

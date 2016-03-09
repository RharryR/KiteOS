// string.c
// Written by Harry Rigg
// Utilites for working with strings of data

#include <string.h>

// Compares to areas of memory
int
memcmp(const void* ptr, const void* bptr, size_t size)
{
	const uint8_t *a = (const uint8_t*) ptr;
	const uint8_t *b = (const uint8_t*) bptr;
	for(size_t i = 0; i < size; i++)
		if ( a[i] < b[i] )
			return -1;
		else if( b[i] < a[i] )
			return 1;
	return 0;	
}

// Sets a area of memory to the specified value (byte)
void*
memset(void* bufptr, int value, size_t size)
{
	uint8_t *buf = (uint8_t*) bufptr;
	for( size_t i = 0; i < size; i++ )
		buf[i] = (uint8_t) value;
	return bufptr;
}

uint16_t*
memsetw(uint16_t* bufptr, uint16_t value, size_t size)
{
	uint16_t *buf=(uint16_t*) bufptr;
	for(; size !=0 ; size--) *buf++ = value;
	return bufptr;
}

// Copys data from a pointer and moves it to another
void*
memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size)
{
	uint8_t *dst = (uint8_t*)dstptr;
	const uint8_t *src = (const uint8_t*) srcptr;
	for( size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr; 
}

// Returns the size of a string
size_t 
strlen(const char* str)
{
	size_t result = 0;
	while( str[result] )
		result ++;
	return result;
}

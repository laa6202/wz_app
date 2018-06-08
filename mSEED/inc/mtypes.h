#ifndef __MTYPES_H
#define __MTYPES_H

typedef unsigned char U8;
typedef unsigned int  U32;
typedef unsigned short U16;
typedef short S16;
typedef int		S32;

typedef struct{
	U16 year,
	U16 day,
	U8	hour,
	U8	min,
	U8	sec,
	U8	res,
	U16	us100
} BTIME,*pBTIME;
 

typedef struct{
	char seq[6],
	char quality,
	U16	 offset_block0
} HEAD,*pHEAD;


typedef struct {
	U16	code,
	U16	offset,
	U8	enc,
	U8	order,
	U8	len,
	U8	res
} BLOCK0,*pBLOCK0;



typedef struct {
	U16	code,
	U16	offset,
	U8	quality,
	U8	msec,
	U8	res,
	U8	count
} BLOCK1,*pBLOCK1;


#endif

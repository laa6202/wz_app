#ifndef __MTYPES_H
#define __MTYPES_H

typedef unsigned char U8;
typedef unsigned int  U32;
typedef unsigned short U16;
typedef short S16;
typedef int		S32;

typedef struct{
	U16 year;
	U16 day;
	U8	hour;
	U8	min;
	U8	sec;
	U8	res;
	U16	us100;
} BTIME,*pBTIME;
 
typedef struct{
	char seq[6];
	char quality;
	char res;
	char station[5];
	char location[2];
	char channel[3];
	char network[2];
	BTIME	start;
	U16		num_sample;
	S16		rate;
	S16		mult;
	U8		act_flags;
	U8		io_flags;
	U8		data_flags;
	U8		num_block;
	S32		time_cor;
	U16		offset_data;
	U16	 	offset_block0;
} HEAD,*pHEAD;


typedef struct {
	U16	code;
	U16	offset;
	U8	enc;
	U8	order;
	U8	len;
	U8	res;
} BLOCK0,*pBLOCK0;



typedef struct {
	U16	code;
	U16	offset;
	U8	quality;
	U8	msec;
	U8	res;
	U8	count;
} BLOCK1,*pBLOCK1;


typedef struct{
	U32 W[16];
}	FRAME,*pFRAME;

typedef struct{
	HEAD head;
	BLOCK0 block0;
	BLOCK1 block1;
	FRAME f0;
	FRAME f1;
	FRAME f2;
	FRAME f3;
	FRAME f4;
	FRAME f5;
	FRAME f6;
}	PACK,*pPACK;



#endif

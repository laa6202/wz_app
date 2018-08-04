#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "wzpkg.h"



int CopyWZPKG(pWZPKG dst,const WZPKG src){
	dst->lenLoad = src.lenLoad;
	dst->lenTail = src.lenTail;
	strcpy(dst->head,src.head);
	strcpy(dst->load,src.load);
	strcpy(dst->tail,src.tail);
	strcpy(dst->crc,src.crc);
	dst->index = src.index;
	dst->res = src.res;
	return 0;
}



int CheckWZPKG(pWZPKG src){
	int i =0;	
	int lenByte;

	unsigned char * wzU8;
	wzU8 = CloneWZPKG2Array(*src,&lenByte);		
//	printf("lenByte = %d\n",lenByte);
	int lenWord = lenByte / 2;
//	printf("lenWord = %d\n",lenWord);
	unsigned short wzU16[lenWord];
	for(i=0;i<lenWord;i++){
		wzU16[i] = ( *(wzU8+2*i) << 8) | (*(wzU8+2*i+1));
//		printf("%04x ",wzU16[i]);
	}
	unsigned short crc = wzU16[lenWord-1];
	unsigned short sum = 0;
	unsigned short a = 0;
	for(i=0;i<lenByte-2;i++){
		a = wzU8[i];
		a = a & 0xff;
		sum += a;
	}
	if(sum == crc){
//		printf("......CheckWZPKG OK ......\n");
	;
	}
	else {
		printf("sum = %04x,crc = %04x\n",sum,crc);
		printf("\033[1;31;40m !!!!!!CheckWZPKG CRC Failed!!!!!! \033[0m\n");
		for(int i=0;i<32;i++)
			printf("%02x",wzU8[i]);
		printf("\n");
		for(int i=0;i<32;i++)
			printf("%02x",wzU8[lenByte-32+i]);
		printf("\n");

	  return -1;
	}
	free(wzU8);
	return 0;
}



unsigned char * CloneWZPKG2Array(WZPKG src,int * lenU8){
	int lenByte = src.lenLoad;
	*lenU8 = lenByte;
	int lenTail = src.lenTail;
	unsigned char * dst;
	dst = (unsigned char *) malloc(lenByte * sizeof(unsigned char));
	int i=0;
	for(i=0;i<12;i++){
		*(dst+i) = src.head[i];
//		printf("%02x ",*(dst+i)	);
	}
	for(i=0;i<18000;i++){
		*(dst+i+12) = src.load[i];
//		if(i<30)		printf("%02x ",*(dst+i+12));
	}
	for(i=0;i<lenTail;i++){
		*(dst+i+12+18000) = src.tail[i];
	}
	for(i=0;i<2;i++){
		*(dst+i+12+18000+lenTail) = src.crc[i];
//		printf("%02x ",*(dst+i+18012+lenTail));
	}
//	printf("\n");
	return dst;
}

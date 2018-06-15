//alg_steim2.c

#include <stdio.h>
#include <string.h>

#include "mtypes.h"
#include "alg_steim2.h"


U32 w[16];


int TestAlg(){
	printf("TestAlg\n");
	return 0;
}



int GetFrame0(pFRAME pfrm0,pRAWALL prawAll,int did,int ch,int pos_sof){
	int pos_eof,pos;
	int i;
	U32 w;
	int c[16];
	
	pos = pos_sof;
		w = GetW1(c,prawAll,did,ch,&pos);
		pfrm0->W[1] = w;
	for(i=3;i<16;i++){
		w = GetWs(c,prawAll,did,ch,&pos);
		pfrm0->W[i] = w;
	}
		w = GetW0(c);
		pfrm0->W[0] = w; 
	pos_eof = pos;
	return pos_eof;
}
	

U32 GetW0(const int * c){
	U32 w0 = 0;
	for(int i=1;i<16;i++){
		if(c[i] == 3)	w0 |= (0x3 << (32-2*i));
		if(c[i] == 2)	w0 |= (0x2 << (32-2*i));
		if(c[i] == 1)	w0 |= (0x1 << (32-2*i));
	}
	return w0;
}


U32 GetW1(int *c,pRAWALL prawAll,int did,int ch,int* pos){
	U32 w1;
	int data = 0;
	int x = prawAll->praw[did]->x[*pos];
	int y = prawAll->praw[did]->y[*pos];
	int z = prawAll->praw[did]->z[*pos];
	if(ch==0) data = 	x;
	if(ch==1) data = 	y;
	if(ch==2) data = 	z;
	*pos++;
	w1 = data;
	c[1] = 0;
	printf("GetW1 : pos = %d,data = %d,w1 = %d\n",*pos,data,w1);
	return w1;
}


U32 GetWs(int *c,pRAWALL prawAll,int did, int ch,int *pos){
	U32 w;
	int data[8];
	int diff[7];
	int i;
	int x,y,z;

	printf("GetWs : ");
	
	for(i=0;i<8;i++){
		x = prawAll->praw[did]->x[*pos];
		printf("[%d]:%d  ",*pos,x);
		*pos = *pos + 1;	
	}

	printf("\n");

	return w;
}





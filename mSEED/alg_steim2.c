//alg_steim2.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mtypes.h"
#include "alg_steim2.h"


//U32 w[16];


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
	c[0] = 0;
	w = GetW1(&c[1],prawAll,did,ch,&pos);
	pfrm0->W[1] = w;
	for(i=3;i<16;i++){
		w = GetWs(c+i,prawAll,did,ch,&pos);
		pfrm0->W[i] = w;
	}
	w = GetW0(c);
	pfrm0->W[0] = w; 
	ChangeEndianFrm(pfrm0);

	pos_eof = pos;
//	printf("pos_eof of Frm0 = %d\n",pos_eof);
	return pos_eof;
}
	


int GetFrames(pFRAME pfrm,pRAWALL prawAll,int did,int ch,int pos_sof){
	int pos, pos_eof;
	int i;
	U32 w;
	int c[16];

	pos = pos_sof;
	c[0] = 0;
	for(i=1;i<16;i++){
		w = GetWs(c+i,prawAll,did,ch,&pos);
		pfrm->W[i] = w;
//		printf("pos = %d  ",pos);
	}
	w = GetW0(c);
	pfrm->W[0] = w; 
	ChangeEndianFrm(pfrm);

	pos_eof =  pos;
	return pos_eof;
}




U32 GetW0(const int * c){
	U32 w0 = 0;
	for(int i=0;i<16;i++){
		if(c[i] == 3)	w0 |= (0x3 << (30-2*i));
		if(c[i] == 2)	w0 |= (0x2 << (30-2*i));
		if(c[i] == 1)	w0 |= (0x1 << (30-2*i));
	}
//	printf("w0 = %08x\n",w0);
	return w0;
}


U32 GetW1(int *c,pRAWALL prawAll,int did,int ch,int* pos){
	U32 w1;
	int pos1 = *pos;
	int data = 0;
	int x = prawAll->praw[did]->x[pos1];
	int y = prawAll->praw[did]->y[pos1];
	int z = prawAll->praw[did]->z[pos1];
	if(ch==0) data = 	x;
	if(ch==1) data = 	y;
	if(ch==2) data = 	z;
	*pos = pos1 +1;
	w1 = data;
	*c = 0;
//	printf("GetW1 : pos = %d,data = %d,w1 = %d\n",pos1,data,w1);
	return w1;
}


U32 GetWs(int *c,pRAWALL prawAll,int did, int ch,int *pos){
	U32 w;
	int data[8];
	int diff[7];
	int i;
	int x,y,z;
	int pos1 = *pos;

//	printf("GetWs : ");
	PreDiffData(diff,prawAll,did,ch,*pos);	
	int diffR = DiffRange(diff);
	w = BuildWs(diff,diffR);
//	printf("0x%08x\t%d\t%d",w,diffR,pos1);
//	printf("\n");
	if(diffR == 4) *c = 1;
	else if(diffR <4) *c = 2;
	else if(diffR >4) *c = 3;
	else *c = 0;
	pos1 += diffR;
	*pos = pos1;
	return w;
}


int PreDiffData(int *diff,pRAWALL prawAll,int did,int ch,int pos){
	int data[8];
	int pos1 = pos;
	if(ch==0) data[0] = prawAll->praw[did]->x[pos1];
	if(ch==1) data[0] = prawAll->praw[did]->y[pos1];
	if(ch==2) data[0] = prawAll->praw[did]->z[pos1];
	diff[0] = 0;
	for(int i=0;i<8;i++){
		if(ch==0) data[i] = prawAll->praw[did]->x[pos1];
		if(ch==1) data[i] = prawAll->praw[did]->y[pos1];
		if(ch==2) data[i] = prawAll->praw[did]->z[pos1];
		diff[i] = data[i] - data[i-1];
//		printf("[%d]:%d:%d  ",pos1,data[i],diff[i]);
		pos1++;	
	}

	return pos1;
}


int DiffRange(int *diff){
	int diffR;
	int maxDiff = 0;
	int absMaxDiff;
	for(int i=1;i<8;i++){	
		maxDiff = (diff[i] > maxDiff) ? diff[i] : maxDiff;
	}
	absMaxDiff = abs(maxDiff);
	if (absMaxDiff <=7 ) return 7;				//4bit
	else if(absMaxDiff <= 15) return 6;		//5bit
	else if(absMaxDiff <= 31) return 5;		//6bit
	else if(absMaxDiff <= 127) return 4;	//8bit
	else if(absMaxDiff <= 511) return 3;	//10bit
	else if(absMaxDiff <= 16383) return 2;	//15bit
	else return 1;

}


U32 BuildWs(int * diff,int diffR){
	U32 w = 0;
	switch(diffR)
	{
		case 1:	w  = (diff[1] & 0x3fffffff);
						w |= (0x1<<30);	break;
		case 2:	w  = (diff[1] & 0x7fff) << 15;
						w |= (diff[2] & 0x7fff) ;	
						w |= (0x2<<30); break;
		case 3:	w  = (diff[1] & 0x3ff) << 20;
						w |= (diff[2] & 0x3ff) << 10;
						w |= (diff[3] & 0x3ff);
						w |= (0x3 << 30); break;
		case 4: w  = (diff[1] & 0xff) << 24;
						w |= (diff[2] & 0xff) << 16;
						w |= (diff[3] & 0xff) << 8;
						w |= (diff[4] & 0xff) ;
		case 5: w  = (diff[1] & 0x3f) << 24;
						w |= (diff[2] & 0x3f) << 18; 
						w |= (diff[3] & 0x3f) << 12; 
						w |= (diff[4] & 0x3f) << 6; 
						w |= (diff[5] & 0x3f) ;
						w |= (0x1 << 30); break;
		case 6: w  = (diff[1] & 0x1f) << 25;
						w |= (diff[2] & 0x1f) << 20;
						w |= (diff[3] & 0x1f) << 15;
						w |= (diff[4] & 0x1f) << 10;
						w |= (diff[5] & 0x1f) << 5;
						w |= (diff[6] & 0x1f) ;
						w |= (0x2 << 30); break;
		case 7: w  = (diff[1] & 0xf) << 24;
						w |= (diff[2] & 0xf) << 20;
						w |= (diff[3] & 0xf) << 16;
						w |= (diff[4] & 0xf) << 12;
						w |= (diff[5] & 0xf) << 8;
						w |= (diff[6] & 0xf) << 4;
						w |= (diff[7] & 0xf) ;
						w |= (0x3 << 30); break;
		default : w = 0;
	}
	return w;
}



int ChangeEndianFrm(pFRAME pfrm){
	U32 b0,b1,b2,b3;
	for(int i=0;i<16;i++){
		b0 = (pfrm->W[i] & 0xff);
		b1 = (pfrm->W[i] & 0xff00) >> 8;
		b2 = (pfrm->W[i] & 0xff0000) >> 16;
		b3 = (pfrm->W[i] & 0xff000000) >> 24;
		pfrm->W[i] = b0 << 24 | b1 << 16 | b2 <<8 | b3;
	}
	return 0;
}

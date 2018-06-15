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
	int pos_eof;
	int i;
	int x,y,z;
	
	i=pos_sof;
	for(;i<pos_sof+7;i++)
	{
		x = prawAll->praw[did]->x[i];
		y = prawAll->praw[did]->y[i];
		z = prawAll->praw[did]->z[i];
		printf("x=%d\ty=%d\tz=%d\n",x,y,z);
	}
	printf("\n");
	pos_eof = i;
	return pos_eof;
}
	



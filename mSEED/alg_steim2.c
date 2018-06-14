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
	pos_eof = pos_sof + 10*ch + 2;
	
	return pos_eof;
}
	



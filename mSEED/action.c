//action.c
//ACtion the module when buf ready,example 30sec one file.

#include <stdio.h>
#include <string.h>


#include "mtypes.h"
#include "action.h"
#include "gen_mseed.h"
#include "gen_par.h"
#include "file_op.h"


int TestStruct(){
	printf("Test struct size only.\n");
	HEAD head;
	FRAME frame;
	PACK pack;
	printf("SIZE of head = %ld\n",sizeof(HEAD));
	printf("SIZE of frame = %ld\n",sizeof(FRAME));
	printf("SIZE of pack = %ld\n",sizeof(PACK));

	return 0;
}


int InitCfgAll(pCFGALL pcfgAll){
	memset(pcfgAll,0,sizeof(CFGALL));
	pcfgAll->posX = 116.44;
	pcfgAll->posY = 40.10;
	return 0;
};

int Action(int did,RAWALL rawAll,CFGALL cfgAll){
	char fnMSeedX[200];	memset(fnMSeedX,0,200);	
	char fnMSeedY[200];	memset(fnMSeedY,0,200);	
	char fnMSeedZ[200];	memset(fnMSeedZ,0,200);

	FnMSeed(fnMSeedX,fnMSeedY,fnMSeedZ,did,NULL);	
	GenMSeed(did,0,rawAll,fnMSeedX);
	return 0;
}



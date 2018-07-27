//action.c
//ACtion the module when buf ready,example 30sec one file.
//Action handle 1 device,gen 3 channel files

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "mtypes.h"
#include "action_mseed.h"
#include "gen_mseed.h"
#include "gen_par.h"
#include "file_op.h"


int TestStruct(){
	printf("Test struct size only.\n");
	MHEAD head;
	FRAME frame;
	PACK pack;
	printf("SIZE of head = %ld\n",sizeof(MHEAD));
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


int ActionMSeed(int did,pRAWALL prawAll,CFGALL cfgAll){
	char fnMSeedX[200];	memset(fnMSeedX,0,200);	
	char fnMSeedY[200];	memset(fnMSeedY,0,200);	
	char fnMSeedZ[200];	memset(fnMSeedZ,0,200);

	struct timeval tv;
	gettimeofday(&tv,NULL);
	printf("ActionMSeed did=%d: begin GenMSeed %d.%06d\n",did,tv.tv_sec,tv.tv_usec);
	if(did <= 20) {
		FnMSeed(fnMSeedX,fnMSeedY,fnMSeedZ,did,NULL);	
		GenMSeed(did,0,prawAll,fnMSeedX);
		GenMSeed(did,1,prawAll,fnMSeedY);
		GenMSeed(did,2,prawAll,fnMSeedZ);
	}
	else 
		printf("Error!\n");
	gettimeofday(&tv,NULL);
	printf("ActionMSeed did=%d: GenMSeed 2 %d.%06d\n",did,tv.tv_sec,tv.tv_usec);

	return 0;
}



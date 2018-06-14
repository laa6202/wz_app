//main.c of mSEED project
//The tb of mSEED alg.

#include <stdio.h>

#include "types.h"

#include "mtypes.h"
#include "action.h"
#include "buf4mseed.h"
#include "btime.h"
#include "file_op.h"
#include "gen_mseed.h"



int main(int argc, char **argv){
	printf("The tb of mSEED project\n");
	WZPKG wzpkg;
	RAWALL rawAll;
	CFGALL cfgAll;
	char fnMSeedX[200];
	char fnMSeedY[200];
	char fnMSeedZ[200];


	InitWZPKG(&wzpkg);
	InitRawAll(&rawAll);
	InitCfgAll(&cfgAll);

	int i=0;
	for(;i<300;i++)
	{

		GenTestWZPKG(&wzpkg,i%3+2);
//		ShowWZPKGInfo(&wzpkg);
		int did = BufWZPKG2Raw(&rawAll,wzpkg);	

		switch(did)
		{
			case 2 : Action(did,rawAll,cfgAll); break;
			case 3 : Action(did,rawAll,cfgAll); break;
			case 4 : Action(did,rawAll,cfgAll); break;
			default : ;
		}	
		
	}
	return 0;
}


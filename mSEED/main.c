//main.c of mSEED project
//The tb of mSEED alg.

#include <stdio.h>

#include "types.h"

#include "mtypes.h"
#include "action_mseed.h"
#include "buf4mseed.h"
#include "btime.h"
#include "file_op.h"
#include "gen_mseed.h"



int main(int argc, char **argv){
	printf("The tb of mSEED project\n");
	WZPKG wzpkg;
	RAWALL rawAll;
	char fnMSeedX[200];
	char fnMSeedY[200];
	char fnMSeedZ[200];


	InitWZPKG(&wzpkg);
	InitRawAll(&rawAll);

	int i=0;
	for(;i<1000;i++)
	{

		GenTestWZPKG(&wzpkg,i%3+2);
//		ShowWZPKGInfo(&wzpkg);
		int did = BufWZPKG2Raw(&rawAll,wzpkg);	
		if(did)
		{
			printf("finish device id = %d,i = %d\n",did,i);
			FnMSeed(fnMSeedX,fnMSeedY,fnMSeedZ,did,NULL);
		}	
	}
	return 0;
}


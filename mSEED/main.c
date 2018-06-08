//main.c of mSEED project
//The tb of mSEED alg.

#include <stdio.h>

#include "types.h"

#include "mtypes.h"
#include "action_mseed.h"
#include "buf4mseed.h"
#include "btime.h"


int main(int argc, char **argv){
	printf("The tb of mSEED project\n");
	WZPKG wzpkg;
	RAWALL rawAll;

	InitWZPKG(&wzpkg);
	InitRawAll(&rawAll);

	int i=0;
	for(;i<100;i++)
	{

		GenTestWZPKG(&wzpkg,i%3+2);
//		ShowWZPKGInfo(&wzpkg);
		int finish = BufWZPKG2Raw(&rawAll,wzpkg);	
		if(finish)
		{
			printf("finish = %d,i = %d\n",finish,i);
		}	
	}
	return 0;
}


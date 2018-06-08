//main.c of mSEED project
//The tb of mSEED alg.

#include <stdio.h>

#include "types.h"

#include "mtypes.h"
#include "action_mseed.h"
#include "buf4mseed.h"

int main(int argc, char **argv){
	printf("The tb of mSEED project\n");
	WZPKG wzpkg;
	for(int i=0;i<100;i++){
		GenTestWZPKG(&wzpkg,i%3);
		ShowWZPKGInfo(&wzpkg);
		
	}
	return 0;
}


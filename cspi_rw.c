#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"


//read FPGA register using CMD struct
int CspiRead(pCMD pcmd){
	printf("......CspiRead......\n");	
	
	time_t now;
	time(&now);
	srand(now+pcmd->res);
	int r = rand(); 
	pcmd->q = r%2;	
	pcmd->res = r & 0xff;
	return 0;
}


int CspiWrite(pCMD pcmd){
	printf("......CspiWrite......\n");	

	return 0;
}

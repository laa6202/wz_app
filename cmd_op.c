#include <stdio.h>

#include "types.h"



int GenCmdPkgRdy(pCMD pcmd){
	printf("......GenCmdPkgRdy......\n");
	pcmd->devid = 0;
	pcmd->rw = 0;
	pcmd->modid = 0x32;
	pcmd->addr = 0x30;
	pcmd->data = 0xff;
	pcmd->q = 0x0;

	return 0;
}


int CheckPkgRdy(const CMD cmd){
	printf("......CheckPkgRdy......\n");
	int pkgRdy = 0;
	if(cmd.q != 0)
		pkgRdy = 1;

	return pkgRdy;
}




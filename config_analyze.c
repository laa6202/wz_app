#include "types.h"
#include <stdio.h>
#include <string.h>

int GetConfig(pCFG pcfg){
	printf("......GetConfig......\n");

	pcfg->remoteHost.port = 5566;
	strcpy(pcfg->remoteHost.ip,"192.168.1.80");
	pcfg->remoteHost.status = 1;

	return 0;
}


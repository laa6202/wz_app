#include "types.h"
#include "stdio.h"
#include "config_analyze.h"

int init(pCFG pcfg){
	printf("...init...\n");
		
	GetConfig(pcfg);
	ShowAllCfg(*pcfg);
	return 0;
}

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config_analyze.h"


int GetConfig(pCFG pcfg){
	printf("......GetConfig......\n");

	char fn[1024];
	CheckCfgFileExist(fn);

	pcfg->remoteHost.port = 5566;
	strcpy(pcfg->remoteHost.ip,"192.168.1.80");
	pcfg->remoteHost.status = 1;

	return 0;
}

int CheckCfgFileExist(char * fn){
	memset(fn,0,sizeof(fn));
	getcwd(fn,1000);
	strcat(fn,"/");
	char filename[20] = "wz1.cfg";
	strcat(fn,filename);
	printf("Configration file name = %s\n",fn);
	int isExist = access(fn,F_OK);
	if(isExist != 0){
		printf("Error: Lost Configuration file in working path.\n");
		printf("Error: The app can not work.\n");
		printf("Note: Please Contact Supplier Immediatiely!\n");
	}
	return isExist;
}



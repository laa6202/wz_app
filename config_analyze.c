#include "types.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config_analyze.h"


int GetConfig(pCFG pcfg){
	printf("......GetConfig......\n");
	char fn[1024];
	int cfgFileExistN = CheckCfgFileExist(fn);
	SetDefaultCfg(pcfg);
	if(cfgFileExistN == 0){
		SetConfig(pcfg,fn);
	}
	return 0;
}

int CheckCfgFileExist(char * fn){
	memset(fn,0,sizeof(fn));
	getcwd(fn,1000);
	strcat(fn,"/");
	char filename[20] = "wz1.cfg";
	strcat(fn,filename);
//	printf("Configration file name = %s\n",fn);
	int isExist = access(fn,F_OK);
	if(isExist != 0){
		printf("Error: Lost Configuration file in working path.\n");
		printf("Error: The app CAN NOT work correctly.\n");
		printf("Note: Please Contact Supplier Immediatiely!\n");
	}
	return isExist;
}



int SetDefaultCfg(pCFG pcfg){

	pcfg->remoteHost.port = 8080;
	strcpy(pcfg->remoteHost.ip,"192.168.0.3");
	pcfg->remoteHost.status = 1;


	return 0;
}


int SetConfig(pCFG pcfg,char * fn){
	FILE * fp = fopen(fn,"r");
	char txtLine[250];
	while(!feof(fp)){
		fgets(txtLine,250,fp);
		char * p1 = strchr(txtLine,'#');
		char * p2 = strchr(txtLine,'=');
//		printf("txtLine = %s",txtLine);
		char key[50],value[200];
		if((p1 == NULL) && (p2 != NULL)){
			
			SeperateKey(key,value,txtLine);
		}
	}
	fclose(fp);
	return 0;
}


int SeperateKey(char * key,char* value,const char * txtLine){
	memset(key,0,sizeof(key));
	memset(value,0,sizeof(value));
	puts(txtLine);


	return 0;
}




#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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
//default Remote host 
	pcfg->remoteHost.port = 8080;
	strcpy(pcfg->remoteHost.ip,"192.168.0.3");
	pcfg->remoteHost.status = 1;
	pcfg->remoteHost.pushOrNot = 0;
//default file name
	time_t now;
	time(&now);
	char cnow[8];
	char fn[250];
	memset(fn,0,sizeof(fn));
	getcwd(fn,sizeof(fn));	
	sprintf(cnow,"%4ld",now);
	strcat(fn,"/rec");
	strcat(fn,cnow);
	strcat(fn,".dat");
	strcpy(pcfg->fNameDef,fn);	
	memset(pcfg->fNameDir,0,sizeof(pcfg->fNameDir));
	memset(pcfg->fNameSeed,0,sizeof(pcfg->fNameSeed));
	pcfg->fUsedID = 0;
	pcfg->dirSaveOrNot = 0;	
//	printf("The default save file name = %s\n",pcfg->fNameDef);

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
		char key[50],value[50];
		if((p1 == NULL) && (p2 != NULL)){
			SeperateKey(key,value,txtLine);
			SetKeyValue(pcfg,key,value);
		}
	}
	fclose(fp);
	return 0;
}


int SeperateKey(char * key,char* value,const char * txtLine){
	memset(key,0,sizeof(key));
	memset(value,0,sizeof(value));
	char cLine[200];
	strcpy(cLine,txtLine);
//	printf("%s \n",cLine);
	int lenLine = strlen(cLine);
//	printf("total = %d\n",lenLine);
	key = strtok(cLine,"=");
	value = strtok(NULL,"=");
//	printf("key = %s\tvalue = %s\n",key,value);

	return 0;
}


int SetKeyValue(pCFG pcfg,const char *key,const char * value){
	if(strcmp(key,"Used File ID")==0){
		pcfg->fUsedID = atoi(value);
		printf("fUsedID = %d\n",pcfg->fUsedID);
	}


	return 0;
}




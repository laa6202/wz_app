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
	pcfg->noCheck = 1;
//default Remote host 
	pcfg->remoteHost.port = 8887;
	strcpy(pcfg->remoteHost.ip,"192.168.0.121");
	pcfg->remoteHost.status = 0;
	pcfg->remoteHost.pushOrNot = 0;
//default direction save file name
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
	strcpy(pcfg->fileDir.fNameDef,fn);	
	pcfg->fileDir.fUsedID = 0;
	memset(pcfg->fileDir.fName,0,sizeof(pcfg->fileDir.fName));
	pcfg->fileDir.saveOrNot = 0;	
	pcfg->fileDir.numOfPkgPreFile=1;
//default miniSeed file 
	memset(pcfg->fNameSeed,0,sizeof(pcfg->fNameSeed));
	return 0;
}


int SetConfig(pCFG pcfg,char * fn){
	FILE * fp = fopen(fn,"r");
	char txtLine[250];
	while(!feof(fp)){
		fgets(txtLine,250,fp);
		char * find = strchr(txtLine,'\n');
		if(find)
			*find = '\0';
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
	char * key2;
	char * value2;
	char cLine[200];
	strcpy(cLine,txtLine);
//	printf("%s \n",cLine);
	int lenLine = strlen(cLine);
//	printf("total = %d\n",lenLine);
	key2 = strtok(cLine,"=");
	value2 = strtok(NULL,"=");
	strcpy(key,key2);
	strcpy(value,value2);
//	printf("Seperate : key = %s\tvalue = %s\n",key,value);
	return 0;
}


int SetKeyValue(pCFG pcfg,const char *key,const char * value){
//global 
	if(strcmp(key,"noCheck") == 0)
		pcfg->noCheck = atoi(value);

//remoteHost
	if(strcmp(key,"remoteHost.ip")==0)
		strcpy(pcfg->remoteHost.ip,value);
	if(strcmp(key,"remoteHost.port")==0)
		pcfg->remoteHost.port = atoi(value);
	if(strcmp(key,"remoteHost.pushOrNot")==0)
		pcfg->remoteHost.pushOrNot = atoi(value);

//dirFile
	if(strcmp(key,"fileDir.fName")==0){
		strcpy(pcfg->fileDir.fName,value);
	}
	if(strcmp(key,"fileDir.fUsedID")==0){
		pcfg->fileDir.fUsedID = atoi(value);
	}
	if(strcmp(key,"fileDir.saveOrNot")==0){
		pcfg->fileDir.saveOrNot = atoi(value);
	}
	if(strcmp(key,"fileDir.numOfPkgPreFile")==0){
		pcfg->fileDir.numOfPkgPreFile = atoi(value);
	}


	return 0;
}



int ShowAllCfg(const CFG cfg){
	printf("noCkeck = %d\n",cfg.noCheck);
//remoteHost
	printf("remoteHost.ip = %s\n",cfg.remoteHost.ip);
	printf("remoteHost.port = %d\n",cfg.remoteHost.port);
	printf("remoteHost.status = %d\n",cfg.remoteHost.status);
	printf("remoteHost.pushOrNot = %d\n",cfg.remoteHost.pushOrNot);
//fileDir
	printf("fileDir.fNameDef = %s\n",cfg.fileDir.fNameDef);
	printf("fileDir.fName = %s\n",cfg.fileDir.fName);
	printf("fileDir.fUsedID = %d\n",cfg.fileDir.fUsedID);
	printf("fileDir.saveOrNot = %d\n",cfg.fileDir.saveOrNot);
	printf("fileDir.numOfPkgPreFile = %d\n",cfg.fileDir.numOfPkgPreFile);


	return 0;
}





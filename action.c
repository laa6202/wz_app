#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "action.h"
#include "types.h"
#include "cmd_op.h"
#include "pspi_read.h"
#include "cspi_rw.h"
#include "dir_save.h"
#include "key_read.h"
#include "wzpkg.h"
#include "send_to_net.h"

#include "mtypes.h"
#include "buf4mseed.h"
#include "action_mseed.h"
#include "alg_steim2.h"


	static int glb_did;
	static pRAWALL glb_prawAll;
	static CFGALL glb_cfgAll;


int action(CFG cfg,SPI cSPI,SPI pSPI,pKEY pkey,int sock,pRAWALL prawAll,pCFGALL pcfgAll){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	printf("---------- action main %d:%06d----------\n",tv.tv_sec%1000,tv.tv_usec);

	WZPKG wzpkg;
	InitWZPKG(&wzpkg);
	CMD cmdCheckPkg;
	int pkgRdy = 0;
	static int index = 1;

	pkgRdy = KeyRead(pkey);
	if(pkgRdy){

		PspiRead(&wzpkg,&pSPI);
		ShowPKGInfo(index++,wzpkg);
		int ret = 0;
		ret = CheckWZPKG(&wzpkg);
		SaveOneWZPKG(cfg,wzpkg);	
    SendOneWZPKG(cfg,sock,wzpkg);	
		ShowStat(cfg,wzpkg,ret);
		if((cfg.noCheck == 0)&&(ret == -1))
			_exit(-1);
		
		if( BufInitSeek(wzpkg) == 1)
			return 0;

		int did = BufWZPKG2Raw(prawAll,wzpkg);

		switch(did)
		{
			case 1 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 2 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 3 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 4 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 5 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 6 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 7 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 8 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 9 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 10 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 11 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 12 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 13 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 14 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 15 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 16 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 17 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 18 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 19 : MainMSeed(did,prawAll,*pcfgAll); break;
			case 20 : MainMSeed(did,prawAll,*pcfgAll); break;
			default :;
		}

	}

	return 0;
}


int MainMSeed(int did,pRAWALL prawAll,CFGALL cfgAll){
	pthread_t pid1;

	PrepareData(did,prawAll,cfgAll);
//	(void *)ThreadMSeed(NULL);
	int err = pthread_create(&pid1,NULL,ThreadMSeed,NULL);
//	int err = pthread_create(&pid1,NULL,ThreadTest,NULL);
	return 0;
}


int PrepareData(int did,pRAWALL prawAll,CFGALL cfgAll){
	glb_did = did;
	glb_prawAll = prawAll;
	glb_cfgAll = cfgAll;
//	ShowRawP(glb_did,glb_prawAll);
	return 0;
}


void *ThreadMSeed(void * arg){
	InterP(glb_did,glb_prawAll);
	ActionMSeed(glb_did,glb_prawAll,glb_cfgAll);
	pthread_detach(pthread_self());
}


void *ThreadTest(void * arg){
	pthread_detach(pthread_self());
}



int ShowCMD(CMD cmd){
	printf("CMD:devid=0x%x,rw=0x%x,modoid=0x%x,addr=0x%x,data=0x%x,q=0x%x\n",\
				cmd.devid,cmd.rw,cmd.modid,cmd.addr,cmd.data,cmd.q);
	return 0;
}


int ShowPKGInfo(int index,WZPKG wzpkg){
	struct timeval tv;
	gettimeofday(&tv,NULL);

	U8 devid = wzpkg.head[1];
	U8 utc[5],ns[5];
	memset(utc,0,5*sizeof(U8));
	memset(ns,0,5*sizeof(U8));
	utc[0] = wzpkg.head[7];
	utc[1] = wzpkg.head[6];
	utc[2] = wzpkg.head[5];
	utc[3] = wzpkg.head[4];
	ns[0] = wzpkg.head[11];
	ns[1] = wzpkg.head[10];
	ns[2] = wzpkg.head[9];
	ns[3] = wzpkg.head[8];
	long ns_int = ns[3] << 24 | ns[2] << 16 | ns[1] << 8 | ns[0]; 
	long utc_int = utc[3] << 24 | utc[2] << 16 | utc[1] << 8 | utc[0];
	printf("index=%d,Devid=%02x,utc=0x%02x%02x%02x%02x,",index,devid,utc[3],utc[2],utc[1],utc[0]);
//	printf("ns=0x%02x%02x%02x%02x\n",ns[3],ns[2],ns[1],ns[0]);
	printf("ns = %ld,",ns_int);
	printf("t = %d:%06d\n",tv.tv_sec%1000,tv.tv_usec);

	static int indexAll[20];
	static int utcAll[20];
	indexAll[devid] ++;
	
	if((utcAll[devid] != utc_int - 1) & (indexAll[devid] != 1)){
		char strW[200]; memset(strW,0,200*sizeof(char));
		strcpy(strW,"ShowPkgInfo : ");
		sprintf(strW,"\033[31m UTC Not ++ did = %d,last_utc = %x,utc_now = %x \033[0m \n",devid,utcAll[devid],utc_int);
		printf("%s",strW);
		LogStr(strW);
	}
	utcAll[devid] = utc_int;

	return 0;
}


int ShowStat(CFG cfg,WZPKG pkg,int check){
	static int totalPkg = 0;
	static int numPkgCh[10];
//	static int numPkgCh8 = 0;
	static int errPkgCh[10];
//	static int errPkgCh8 = 0;
	
	U8 ch = pkg.head[1];
	totalPkg ++;
	for(int i=0;i<10;i++){
		if(ch == i){
		numPkgCh[i] ++;
		if(check == -1)
			errPkgCh[i] ++;
		}
	}

	printf("total=%d  ",totalPkg);
	for(int i=1;i<9;i++){
		printf("[%d]=%d,E=%d  ",i,numPkgCh[i],errPkgCh[i]);
	}
	printf("\n");
	return 0;
}




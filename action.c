#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "action.h"
#include "types.h"
#include "cmd_op.h"
#include "pspi_read.h"
#include "cspi_rw.h"
#include "dir_save.h"
#include "key_read.h"
#include "wzpkg.h"
#include "send_to_net.h"


int action(CFG cfg,SPI cSPI,SPI pSPI,pKEY pkey,int sock){
	printf("--- action main ---\n");
	WZPKG wzpkg;
	InitWZPKG(&wzpkg);
	CMD cmdCheckPkg;
	int pkgRdy = 0;
	static int index = 0;

//		GenCmdPkgRdy(&cmdCheckPkg);	
//		CspiRead(&cmdCheckPkg,&cSPI);
//		ShowCMD(cmdCheckPkg);
//		pkgRdy = CheckPkgRdy(cmdCheckPkg);
	pkgRdy = KeyRead(pkey);
	if(pkgRdy){
		PspiRead(&wzpkg,&pSPI);
		ShowPKGInfo(index++,wzpkg);
		//SaveSomeWZPKG(cfg,wzpkg,0);		
		int ret = CheckWZPKG(&wzpkg);
		SaveOneWZPKG(cfg,wzpkg);	
    SendOneWZPKG(cfg,sock,wzpkg);	
		ShowStat(cfg,wzpkg,ret);
   // echo_cli(sock); 
		if((cfg.noCheck == 0)&&(ret == -1))
			_exit(-1);
	}	
	
	return 0;
}


int ShowCMD(CMD cmd){
	printf("CMD:devid=0x%x,rw=0x%x,modoid=0x%x,addr=0x%x,data=0x%x,q=0x%x\n",\
				cmd.devid,cmd.rw,cmd.modid,cmd.addr,cmd.data,cmd.q);
	return 0;
}


int ShowPKGInfo(int index,WZPKG wzpkg){
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
	printf("index=%d \tDevid=%02x\tutc=0x%02x%02x%02x%02x\t",index,devid,utc[3],utc[2],utc[1],utc[0]);
	printf("ns=0x%02x%02x%02x%02x\n",ns[3],ns[2],ns[1],ns[0]);

	return 0;
}


int ShowStat(CFG cfg,WZPKG pkg,int check){
	static int totalPkg = 0;
	static int numPkgCh2 = 0;
	static int numPkgCh8 = 0;
	static int errPkgCh2 = 0;
	static int errPkgCh8 = 0;
	
	U8 ch = pkg.head[1];
	totalPkg ++;
	if(ch == 2) {
		numPkgCh2 ++;
		if(check == -1)
			errPkgCh2 ++;
	}
	else if(ch == 8){
		numPkgCh8++;
		if(check == -1)
			errPkgCh8 ++;
	}
	printf("total=%d,\tDev2=%d,Dev8=%d,\terrDev2=%d,errDev8=%d\n",totalPkg,numPkgCh2,numPkgCh8,errPkgCh2,errPkgCh8);
	return 0;
}



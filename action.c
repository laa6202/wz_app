#include <stdio.h>
#include <unistd.h>

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
		printf("index = %d \tpkgLen = %d\n",index++,wzpkg.lenLoad);
		PspiRead(&wzpkg,&pSPI);
		//SaveSomeWZPKG(cfg,wzpkg,0);		
		int ret = CheckWZPKG(&wzpkg);
		SaveOneWZPKG(cfg,wzpkg);	
    SendOneWZPKG(sock,wzpkg);	
   // echo_cli(sock); 
		if(ret == -1)
			_exit(-1);
	}	
	
	return 0;
}


int ShowCMD(CMD cmd){
	printf("CMD:devid=0x%x,rw=0x%x,modoid=0x%x,addr=0x%x,data=0x%x,q=0x%x\n",\
				cmd.devid,cmd.rw,cmd.modid,cmd.addr,cmd.data,cmd.q);
	return 0;
}




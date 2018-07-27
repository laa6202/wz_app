#include <stdio.h>
#include <unistd.h>

#include "init.h"
#include "action.h"
#include "types.h"
#include "key_read.h"
#include "send_to_net.h"
#include "dir_save.h"

#include "mtypes.h"
#include "action_mseed.h"
#include "buf4mseed.h"

//#define SIM

int sock=0;

int main(int argc ,char ** argv){
	
	printf("wz_app\n");
	chdir("/home");
	LogBegin();
	
	CFG cfg;
	SPI cSPI,pSPI;
	KEY key;
	RAWALL rawAll;
	CFGALL cfgAll;

	InitCfg(&cfg);
	InitSPI(&cSPI,&pSPI);
	KeyInit(&key);
	InitRawAll(&rawAll);
	InitCfgAll(&cfgAll);
		
  sock = InitSocket();
//	for(int i=0;i<40;i++){
	while(1){
		action(cfg,cSPI,pSPI,&key,sock,&rawAll,&cfgAll);
	}
	EndSPI(cSPI,pSPI);
	KeyClose(&key);
	
	return 0;
}

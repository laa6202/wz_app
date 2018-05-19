#include <stdio.h>
#include "init.h"
#include "action.h"
#include "types.h"
#include "key_read.h"

#include "send_to_net.h"

//#define SIM

int sock=0;

int main(int argc ,char ** argv){
	
	printf("wz_app\n");
	
	CFG cfg;
	SPI cSPI,pSPI;
	KEY key;
	InitCfg(&cfg);
	InitSPI(&cSPI,&pSPI);
	KeyInit(&key);
	
  sock = InitSocket();
//	for(int i=0;i<40;i++){
	while(1){
		action(cfg,cSPI,pSPI,&key,sock);
	}
	EndSPI(cSPI,pSPI);
	KeyClose(&key);
	
	return 0;
}

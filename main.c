#include <stdio.h>
#include "init.h"
#include "action.h"
#include "types.h"
#include "key_read.h"

//#define SIM

int main(int argc ,char ** argv){
	
	printf("wz_app\n");
	
	CFG cfg;
	SPI cSPI,pSPI;
	KEY key;
	InitCfg(&cfg);
	InitSPI(&cSPI,&pSPI);
	KeyInit(&key);
	
	do{

		action(cfg,cSPI,pSPI,key);
	}while(0);
	EndSPI(cSPI,pSPI);
	KeyClose(&key);
	
	return 0;
}

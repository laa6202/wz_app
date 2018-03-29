#include <stdio.h>
#include "init.h"
#include "action.h"
#include "types.h"

//#define SIM

int main(int argc ,char ** argv){
	
	printf("wz_app\n");
	
	CFG cfg;
	SPI cSPI,pSPI;
	InitCfg(&cfg);
	InitSPI(&cSPI,&pSPI);
	do{

		action(cfg,cSPI,pSPI);
	}while(0);
	EndSPI(cSPI,pSPI);
	
	return 0;
}

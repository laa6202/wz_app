#include "stdio.h"
#include "unistd.h"

#include "types.h"
#include "config_analyze.h"
#include "cspi_rw.h"
#include "pspi_read.h"


int InitCfg(pCFG pcfg){
	printf("...init...\n");
		
	GetConfig(pcfg);
	ShowAllCfg(*pcfg);
	return 0;
}


int InitSPI(pSPI pcSPI,pSPI ppSPI){
	ppSPI->device = "/dev/spidev0.0";
	ppSPI->bits = 8;
	ppSPI->speed = 20000000;
#ifndef SIM
	PspiInit(ppSPI);
#endif

	pcSPI->device = "/dev/spidev1.0";
	pcSPI->bits = 8;
	pcSPI->speed = 100000;
#ifndef SIM
	CspiInit(pcSPI);
#endif

	return 0;
}


int EndSPI(SPI cSPI,SPI pSPI){
	close(cSPI.fd);
	close(pSPI.fd);
	return 0;
}




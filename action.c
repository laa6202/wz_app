#include "action.h"
#include <stdio.h>
#include "types.h"
#include "send_DS7.h"
#include "pspi_read.h"


int action(CFG cfg){
	printf("...action...\n");
	WZPKG wzpkg;
	

	if(1)
		PspiRead(&wzpkg);


	SendDS7(cfg,wzpkg);
	return 0;
}

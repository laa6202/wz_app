#include "action.h"
#include <stdio.h>
#include "types.h"
#include "pspi_read.h"


int action(CFG cfg){
	printf("...action...\n");
	WZPKG wzpkg;
	

	if(1)
		PspiRead(&wzpkg);


	return 0;
}

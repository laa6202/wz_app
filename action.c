#include "action.h"
#include <stdio.h>
#include "types.h"
#include "cmd_op.h"
#include "pspi_read.h"
#include "cspi_rw.h"


int action(CFG cfg){
	printf("...action...\n");
	WZPKG wzpkg;
	CMD cmdCheckPkg;
//while(1)
	if(1){
		GenCmdPkgRdy(&cmdCheckPkg);	
		CspiRead(&cmdCheckPkg);
		PspiRead(&wzpkg);

	}
	return 0;
}

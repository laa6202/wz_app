#include <stdio.h>

#include "action.h"
#include "types.h"
#include "cmd_op.h"
#include "pspi_read.h"
#include "cspi_rw.h"
#include "dir_save.h"


int action(CFG cfg){
	printf("...action...\n");
	WZPKG wzpkg;
	InitWZPKG(&wzpkg);
	CMD cmdCheckPkg;
	int pkgRdy = 0;
//while(1)
	for(int i=0;i<4;i++)
	{
		printf("--- action main ---\n");
		GenCmdPkgRdy(&cmdCheckPkg);	
		CspiRead(&cmdCheckPkg);
		pkgRdy = CheckPkgRdy(cmdCheckPkg);
		if(pkgRdy){
			PspiRead(&wzpkg);
			SaveSomeWZPKG(cfg,wzpkg,0);		
		}	
	}
	return 0;
}



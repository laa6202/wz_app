#include <stdio.h>
#include "init.h"
#include "action.h"

int main(int argc ,char ** argv){
	
	printf("wz_app\n");
	
	CFG cfg;
	init(&cfg);

	do{


		action(cfg);
	}while(0);

	return 0;
}

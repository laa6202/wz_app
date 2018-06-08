#include <stdio.h>
#include <time.h>

#include "types.h"
#include "mtypes.h"
#include "btime.h"


int TestTime(){
	printf("TestTime...\n");
	time_t now;
	struct tm * tmNow;
	char  * cNow;
	time(&now);
	printf("sizeof now = %ld\n",sizeof(time_t));
	printf("now = %ld\n",now);
	tmNow = gmtime(&now);
	cNow = ctime(&now);
	printf("cNow = %s",cNow);

	time_t mod1;
	char * cMod1;
	mod1 = now - 86400;
	cMod1 = ctime(&mod1);
	printf("cMod1 = %s",cMod1);

	time_t mod2;
	mod2 = 17532 * 86400 - 3600 * 8;
	char * cMod2;
	cMod2 = ctime(&mod2);
	printf("cMod2 = %s",cMod2);
	return 0;
}


int CovWZ2BTIME(pBTIME pbtime,WZPKG wzpkg){


}


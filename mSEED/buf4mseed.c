//buf4mseed.c
//Every time one WZPKG ready, call the buf function.

#include <stdio.h>
#include <string.h>

#include "types.h"

#include "mtypes.h"
#include "buf4mseed.h"

int InitWZPKG(pWZPKG pwzpkg){
	memset(pwzpkg,0,sizeof(WZPKG));
	return 0;
}


int GenTestWZPKG(pWZPKG pwzpkg,int ch){
	int index = pwzpkg->index;
	int start_utc = START_UTC + index * 30;
	int start_ns  = START_NS;
	pwzpkg->lenLoad = 18062;
	pwzpkg->lenTail = 48;
	pwzpkg->head[0] = 0x51;
	pwzpkg->head[1] = (ch & 0xff);
	pwzpkg->head[2] = 0x47;
	pwzpkg->head[3] = 0x02;
	//pwzpkg->head[4] = 
	return 0;
}


int ShowWZPKGInfo(pWZPKG pwzpkg){

	return 0;
}



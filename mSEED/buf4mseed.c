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
	pwzpkg->head[4] = ((start_utc & 0xff000000) >> 24);
	pwzpkg->head[5] = ((start_utc & 0xff0000) >> 16);
	pwzpkg->head[6] = ((start_utc & 0xff00) >> 8);
	pwzpkg->head[7] = (start_utc & 0xff);
	pwzpkg->head[8] = ((start_ns & 0xff000000) >> 24);
	pwzpkg->head[9] = ((start_ns & 0xff0000) >> 16);
	pwzpkg->head[10] = ((start_ns & 0xff00) >> 8);
	pwzpkg->head[11] = (start_ns & 0xff);

	int x,y,z;
	for (int i=0;i<2000;i++){
		x = i*10;
		pwzpkg->load[i*9] = (x & 0xff0000) >> 16;	
		pwzpkg->load[i*9+1] = (x & 0xff00) >> 8;	
		pwzpkg->load[i*9+2] = (x & 0xff);	
	}
	pwzpkg->index++;
	return 0;
}


int ShowWZPKGInfo(pWZPKG pwzpkg){
	printf("WZPKG index = %d\t",pwzpkg->index);
	int utc = (pwzpkg->head[4] << 24 ) | (pwzpkg->head[5] << 16);
	utc += (pwzpkg->head[6] << 8);
	utc += (pwzpkg->head[7]);	
	printf("utc = 0x%08x\n",utc);

	int x,y,z;
	for(int i=0;i<2000;i++){

	}
	return 0;
}



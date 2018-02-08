#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "pspi_read.h"

int PspiRead(pWZPKG pwzpkg){
	printf("......PspiRead......\n");
	
	MakeWZPKG(pwzpkg);
	printf("index of wzpkg = %d\n",pwzpkg->index);
	return 0;
}


int InitWZPKG(pWZPKG pwzpkg){
	pwzpkg->index = 0;
	pwzpkg->res = 0;
	return 0;
}


int MakeWZPKG(pWZPKG pwzpkg){
	int i=0;
	pwzpkg->lenLoad = 18062;
	pwzpkg->lenTail = 48;

	memset(pwzpkg->head,0,sizeof(pwzpkg->head));
	pwzpkg->head[0] = 0x57;
	pwzpkg->head[1] = rand()%10;
	pwzpkg->head[2] = 0x04;
	pwzpkg->head[3] = 0xD0;
	pwzpkg->head[6] = 0x01;
	pwzpkg->head[7] = 0x02;
	pwzpkg->head[8] = rand() & 0xff;
	pwzpkg->head[9] = rand() & 0xff;
	pwzpkg->head[10] = rand() & 0xff;
	pwzpkg->head[11] = rand() & 0xff;

	memset(pwzpkg->load,0,sizeof(pwzpkg->load));
	for(i=0;i<2000;i++){
		pwzpkg->load[i*9] = i & 0xff;	
		pwzpkg->load[i*9+1] = i & 0xff;	
		pwzpkg->load[i*9+2] = i & 0xff;	
		pwzpkg->load[i*9+3] = 0x22;	
		pwzpkg->load[i*9+4] = 0x22;	
		pwzpkg->load[i*9+5] = 0x22;	
		pwzpkg->load[i*9+6] = 0x33;	
		pwzpkg->load[i*9+7] = 0x33;	
		pwzpkg->load[i*9+8] = 0x33;	
	}

	memset(pwzpkg->tail,0,sizeof(pwzpkg->tail));
	for(i=0;i<32;i++)
	{
		pwzpkg->tail[16+i] = i;
	}

	int crc = 0;
	for(i=0;i<12;i++)
		crc += pwzpkg->head[i];
	for(i=0;i<18000;i++)
		crc += pwzpkg->load[i];
	for(i=0;i<pwzpkg->lenTail;i++)
		crc += pwzpkg->tail[i];
	pwzpkg->crc[0] = (crc & 0xff00) >> 8;
	pwzpkg->crc[1] = (crc & 0xff);

	pwzpkg->index ++;
	return 0;
}


int init_rand(){
	time_t now;
	time(&now);
	srand(now);
	return 0;
} 



